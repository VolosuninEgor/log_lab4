#include <iostream>
#include <random>
#include <utility>

struct Node {
    int data;
    struct Node *left{nullptr};
    struct Node *right{nullptr};

    Node(int dt) : data(dt) {}
};


Node *createTree(Node*& node, int data, bool fNoDup) {
    if (node == nullptr) {
        node = new Node(data);
        return node;
    }
    if (fNoDup && data == node->data) return nullptr;
    else if (data > node->data) return createTree(node->right, data, fNoDup);
    else return createTree(node->left, data, fNoDup);
}

void printTree(Node *r, int level = 0) {
    if (r == nullptr) return;

    printTree(r->right, level + 1);
    for (int i = 0; i < level; ++i) {
        std::cout << "  ";
    }
    std::cout << r->data << "\n";
    printTree(r->left, level + 1);
}

void genTree(Node *&node, int size, std::mt19937& gen, bool fNoDup) {
    std::uniform_int_distribution<int> distrib(1, 100);
    //std::cout << "данные: \n";
    if (size > 100) size = 100;
    while (size > 0) {
        int data = distrib(gen);
        //std::cout << data << " ";
        if (createTree(node, data, fNoDup) == nullptr) continue;        
        --size;
    }
    std::cout << "\n\n";
}

Node* search(Node *node, int data) {
    if (node == nullptr) return nullptr;
    if (data == node->data) return node;
    
    if (data > node->data) return search(node->right, data);
    else return search(node->left, data);
}

int countOccurrences(Node *node, int data) {
    if (node == nullptr) return 0;
    int count = (node->data == data) ? 1 : 0;
    return count + countOccurrences(node->left, data)
                 + countOccurrences(node->right, data); 
}

void clearTree(Node*& node) {
    if (node == nullptr) return;
    clearTree(node->right);
    clearTree(node->left);
    delete(node);
    node = nullptr;
}

int main() {
    Node *node = nullptr;
    bool command, fNoDup;

    std::cout << "режим работы:\n";
    std::cout << "0 ручной ввод (-1 = конец)\n";
    std::cout << "1 генерация дерева заданного размера\n";
    std::cout << "номер: ";
    std::cin >> command;
    std::cout << "дополнительно: \n";
    std::cout << "0 дерево с повторениями\n";
    std::cout << "1 дерево без повторений\n";
    std::cin >> fNoDup;

    if (!command) {
        int data;
        std::cout << "ввод даных:\n";
        while(std::cin >> data) {
            if (data == -1) break;
            else createTree(node, data, fNoDup);        
        }
    } else {
        int size;
        std::cout << "введите количество элементов: ";
        std::cin >> size;
        
        std::random_device rd;
        std::mt19937 gen(rd());
        genTree(node, size, gen, fNoDup);
    }
    std::cout << "дерево: \n";
    printTree(node);
    
    std::cout << "действия:\n";
    std::cout << "0 поиск заданного значения\n";
    std::cout << "1 подсчет числа вхождений\n";
    std::cout << "номер: ";
    std::cin >> command;
    int data;
    std::cout << "введите число: ";
    std::cin >> data;

    if (!command) {
        Node* res = search(node, data);
        if (res == nullptr) std::cout << "число не существует\n";
        else std::cout << "число существует\n";
    }
    else std::cout << "вхождений: " << countOccurrences(node, data) << "\n";
    
    clearTree(node);
    return 0;
}

