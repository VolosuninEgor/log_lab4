1 доп задание. Подсчет глубины при поиске значений и поиск нескольких значений.


Node* search(Node *node, int data, int depth = 0) {
    if (node == nullptr) return nullptr;
    if (data == node->data) {
        std::cout << "глубина узла: " << depth << "\n";
        search(node->left, data, depth + 1);
        return node;
    }
    
    if (data > node->data) return search(node->right, data, depth + 1);
    else return search(node->left, data, depth + 1);
}

подсчет происходит при помощи рекурсии и возврата глубины, которая увеличивается на единичку при каждой итерации рекурсии. 


2 доп задание. Удаление узла и корректное смещение его потомков. 

Node* findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void deleteNode(Node*& node, int data) {
    if (node == nullptr) return;

    if (data < node->data) {
        deleteNode(node->left, data);
    } else if (data > node->data) {
        deleteNode(node->right, data);
    } else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            node = temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            node = temp;
        } else {
            Node* temp = findMin(node->right);
            node->data = temp->data;
            deleteNode(node->right, temp->data);
        }
    }
}
 

Реализована основная функция deleteNode:
Сначала ищем введенный узел, сравнивая значения и переходя к соответствующему потомку.
Когда нашли - смотрим потомки. если потомков нет - просто удаляем (указываем на nullptr и наш удаляем узел), если потомок только один - сохраняем во временной переменной, удаляем нынешний узел, присваевам сохраненный. 
Если потомков 2 - делаем шаг вправо и идем до минимального значения слева с помощью вспомогательной функции findMin. Найденный узел сохраняем в временной переменной, меняем значение нынешнего узла на сохраненный во временной переменной, и вызываем функцию для удаления дубликата, который остался внизу дерева. 

