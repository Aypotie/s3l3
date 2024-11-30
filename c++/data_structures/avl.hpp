#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct AVLTreeNode {
    int value;                     // Значение узла
    int height;                    // Высота узла
    AVLTreeNode* left;             // Указатель на левое поддерево
    AVLTreeNode* right;            // Указатель на правое поддерево

    AVLTreeNode(const int val) : value(val), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLTreeNode* head;             // Корень дерева

    // Вспомогательные функции (private)
    int height(AVLTreeNode* node) const;        // Получение высоты узла
    void updateHeight(AVLTreeNode* node);       // Обновление высоты узла
    int getBalance(AVLTreeNode* node) const;    // Получение баланса узла
    AVLTreeNode* rotateRight(AVLTreeNode* y);   // Правое вращение
    AVLTreeNode* rotateLeft(AVLTreeNode* x);    // Левое вращение
    AVLTreeNode* balanceNode(AVLTreeNode* node);// Балансировка узла

    AVLTreeNode* insert(AVLTreeNode* node, int value);  // Рекурсивная вставка
    AVLTreeNode* remove(AVLTreeNode* node, int value);  // Рекурсивное удаление
    AVLTreeNode* getMinValueNode(AVLTreeNode* node) const; // Получение узла с минимальным значением

    AVLTreeNode* search(AVLTreeNode* node, int value) const; // Рекурсивный поиск узла

    // Методы для сериализации и десериализации
    void serializeNode(AVLTreeNode* node, string& result) const;
    AVLTreeNode* unserializeSS(istringstream& ss);

    void serializeBinaryNode(AVLTreeNode* node, ofstream& out) const;
    AVLTreeNode* unserializeBinaryNode(ifstream& in);

public:
    AVLTree();                     // Конструктор
    ~AVLTree();                    // Деструктор
    void clear();                  // Очистка дерева

    // Операции с деревом
    void insertNum(int value);     // Вставка значения
    void removeNum(int value);     // Удаление значения
    AVLTreeNode* find(int value) const; // Поиск значения

    // Сериализация и десериализация
    string serialize() const;      // Сериализация дерева
    void unserialize(const string& data); // Десериализация дерева

    void serializeBinary(const string& filename) const;
    void unserializeBinary(const string& filename);

    // Печать дерева
    friend ostream& operator<<(ostream& os, const AVLTree& tree);
};

// Реализация методов класса AVLTree

AVLTree::AVLTree() : head(nullptr) {}

AVLTree::~AVLTree() {
    clear();
}

// Очистка дерева
void AVLTree::clear() {
    while (head != nullptr) {
        removeNum(head->value);
    }
}

int AVLTree::height(AVLTreeNode* node) const {
    return node == nullptr ? 0 : node->height;
}

void AVLTree::updateHeight(AVLTreeNode* node) {
    if (node != nullptr) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }
}

int AVLTree::getBalance(AVLTreeNode* node) const {
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

AVLTreeNode* AVLTree::rotateRight(AVLTreeNode* y) {
    AVLTreeNode* x = y->left;
    AVLTreeNode* T2 = x->right;

    // Выполняем вращение
    x->right = y;
    y->left = T2;

    // Обновляем высоты
    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLTreeNode* AVLTree::rotateLeft(AVLTreeNode* x) {
    AVLTreeNode* y = x->right;
    AVLTreeNode* T2 = y->left;

    // Выполняем вращение
    y->left = x;
    x->right = T2;

    // Обновляем высоты
    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLTreeNode* AVLTree::balanceNode(AVLTreeNode* node) {
    updateHeight(node);
    int balance = getBalance(node);

    // Левое вращение, если баланс > 1 и вставка произошла в левое поддерево
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    // Правое вращение, если баланс < -1 и вставка произошла в правое поддерево
    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Левое-правое вращение
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Правое-левое вращение
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVLTreeNode* AVLTree::insert(AVLTreeNode* node, int value) {
    if (node == nullptr) {
        return new AVLTreeNode(value);
    }

    if (value < node->value) {
        node->left = insert(node->left, value);
    } else if (value > node->value) {
        node->right = insert(node->right, value);
    } else {
        return node;
    }

    return balanceNode(node);
}

void AVLTree::insertNum(int value) {
    head = insert(head, value);
}

AVLTreeNode* AVLTree::remove(AVLTreeNode* node, int value) {
    if (node == nullptr) {
        return node;
    }

    if (value < node->value) {
        node->left = remove(node->left, value);
    } else if (value > node->value) {
        node->right = remove(node->right, value);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            AVLTreeNode* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            AVLTreeNode* temp = getMinValueNode(node->right);
            node->value = temp->value;
            node->right = remove(node->right, temp->value);
        }
    }

    if (node == nullptr) {
        return node;
    }

    return balanceNode(node);
}

void AVLTree::removeNum(int value) {
    head = remove(head, value);
}

AVLTreeNode* AVLTree::getMinValueNode(AVLTreeNode* node) const {
    AVLTreeNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

AVLTreeNode* AVLTree::search(AVLTreeNode* node, int value) const {
    if (node == nullptr || node->value == value) {
        return node;
    }

    if (value < node->value) {
        return search(node->left, value);
    } else {
        return search(node->right, value);
    }
}

AVLTreeNode* AVLTree::find(int value) const {
    return search(head, value);
}

void AVLTree::serializeNode(AVLTreeNode* node, string& result) const {
    if (node == nullptr) {
        result += "#-";
        return;
    }
    result += to_string(node->value) + "-";
    serializeNode(node->left, result);
    serializeNode(node->right, result);
}

string AVLTree::serialize() const {
    string result;
    serializeNode(head, result);
    return result;
}

void AVLTree::unserialize(const string& data) {
    istringstream ss(data);
    head = unserializeSS(ss);
}

AVLTreeNode* AVLTree::unserializeSS(istringstream& ss) {
    string val;
    getline(ss, val, '-');

    if (val == "#") {
        return nullptr;
    }

    AVLTreeNode* node = new AVLTreeNode(stoi(val));
    node->left = unserializeSS(ss);
    node->right = unserializeSS(ss);

    return node;
}

void AVLTree::serializeBinaryNode(AVLTreeNode* node, ofstream& out) const {
    if (node == nullptr) {
        // Записываем маркер отсутствующего узла
        int nullMarker = -1;
        out.write(reinterpret_cast<const char*>(&nullMarker), sizeof(nullMarker));
        return;
    }

    // Записываем значение узла
    out.write(reinterpret_cast<const char*>(&node->value), sizeof(node->value));

    // Рекурсивно сериализуем левое и правое поддерево
    serializeBinaryNode(node->left, out);
    serializeBinaryNode(node->right, out);
}

AVLTreeNode* AVLTree::unserializeBinaryNode(ifstream& in) {
    int value;

    // Читаем значение узла
    in.read(reinterpret_cast<char*>(&value), sizeof(value));
    if (value == -1) {
        // Если встретили маркер отсутствующего узла, возвращаем nullptr
        return nullptr;
    }

    // Создаем новый узел с прочитанным значением
    AVLTreeNode* node = new AVLTreeNode(value);

    // Рекурсивно восстанавливаем левое и правое поддерево
    node->left = unserializeBinaryNode(in);
    node->right = unserializeBinaryNode(in);

    return node;
}

void AVLTree::serializeBinary(const string& filename) const {
    ofstream out(filename, ios::binary);
    if (!out) {
        throw runtime_error("Failed to open file for binary serialization.");
    }

    serializeBinaryNode(head, out);
    out.close();
}

void AVLTree::unserializeBinary(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) {
        throw runtime_error("Failed to open file for binary deserialization.");
    }

    head = unserializeBinaryNode(in);
    in.close();
}


void printAVLTree(string& result, AVLTreeNode* tree, int depth = 0, string prefix = "", bool hasSibling = false) {
    if (tree == nullptr) {
        return;
    }

    // Рисуем правое поддерево
    if (tree->right != nullptr) {
        printAVLTree(result, tree->right, depth + 1, prefix + (hasSibling ? "│   " : "    "), true);
    }

    // Добавляем текущий узел
    result += prefix;
    if (depth > 0) {
        result += hasSibling ? "┌──" : "└──";
    }
    result += "[" + to_string(tree->value) + "]\n";

    // Рисуем левое поддерево
    if (tree->left != nullptr) {
        printAVLTree(result, tree->left, depth + 1, prefix + (hasSibling ? "│   " : "    "), false);
    }
}

ostream& operator<<(ostream& os, const AVLTree& tree) {
    string stringTree = "";
    printAVLTree(stringTree, tree.head);
    os << stringTree;
    return os;
}

#endif
