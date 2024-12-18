#ifndef SLIST_H
#define SLIST_H

#include <iostream>

using namespace std;

template <typename T>
struct SNode {
    T value;
    SNode<T>* next;

    SNode(const T& val) : value(val), next(nullptr) {}
};

template <typename T>
class SList {
private:
    int len;
    SNode<T>* head;

public:
    SList() {
        head = nullptr;
        len = 0;
    }

    SNode<T>* getHead() const {
        return head;
    }

    int size() const {
        return len;
    }

    void pushForward(T value) {
        SNode<T>* node = new SNode<T>(value);
        SNode<T>* oldHead = head;
        head = node;
        node->next = oldHead;
        len++;
    }

    void pushBack(T value) {
        SNode<T>* node = new SNode<T>(value);
        if (head == nullptr) {
            head = node;
        } else {
            SNode<T>* current = head;
            while (current->next!= nullptr) {
                current = current->next;
            }
            current->next = node;
        }
        len++;
    }

    void removeForward() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        SNode<T>* oldHead = head;
        head = head->next;
        delete oldHead;
        len--;
    }

    void removeBack() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        if (head->next == nullptr) { // Если в списке только один элемент
            delete head;
            head = nullptr;
        } else {
            SNode<T>* current = head;
            while (current->next->next != nullptr) {
                current = current->next; // Находим предпоследний узел
            }
            delete current->next; // Удаляем последний узел
            current->next = nullptr; // Обнуляем указатель на следующий узел
        }
        len--;
    }

    void removeValue(const T& value) {
        SNode<T>* prev = nullptr;
        SNode<T>* current = head;

        while(current != nullptr) {
            if(current->value == value) {
                if (prev != nullptr) {
                    prev->next = current->next;
                    delete current;
                    current = prev->next;
                } else {
                    head = current->next;
                    delete current;
                    current = head;
                }
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    SNode<T>* findByValue(const T& value) {
        SNode<T>* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->value == value) {
                return current;
            }
            current = current->next;
            index++;
        }
        return nullptr;
    }

    string join(char delimiter) {
        string result;
        SNode<string>* current = head;

        while (current != nullptr) {
            result += current->value;
            if (current->next != nullptr) {
                result += delimiter;
            }
            current = current->next;
        }

        return result;
    }
    T get(int index) const {
        if (index < 0 || index >= len) {
            throw runtime_error("Index out of bounds");
        }

        SNode<T>* current = head;
        int c = 0;
        while (c != index && current != nullptr) {
            current = current->next;
            c++;
        }
        return current->value;
    }

    void serializeToBinary(const string& filename) const {
        ofstream outFile(filename, ios::binary);
        if (!outFile) {
            throw runtime_error("Unable to open file for serialization");
        }

        // Сохраняем длину списка
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));

        // Сохраняем значения узлов
        SNode<T>* current = head;
        while (current != nullptr) {
            outFile.write(reinterpret_cast<const char*>(&current->value), sizeof(T));
            current = current->next;
        }

        outFile.close();
    }

    void deserializeFromBinary(const string& filename) {
        ifstream inFile(filename, ios::binary);
        if (!inFile) {
            throw runtime_error("Unable to open file for deserialization");
        }

        // Считываем длину списка
        int newLen;
        inFile.read(reinterpret_cast<char*>(&newLen), sizeof(newLen));

        // Удаляем текущий список
        while (len > 0) {
            removeForward();
        }

        // Считываем значения и восстанавливаем список
        for (int i = 0; i < newLen; i++) {
            T value;
            inFile.read(reinterpret_cast<char*>(&value), sizeof(T));
            pushBack(value);
        }

        inFile.close();
    }

};

template <typename T>
ostream& operator<<(ostream& os, const SList<T>& list) {
    auto head = list.getHead();
    while (head != nullptr) {
        cout << head->value << endl;
        head = head->next;
    }
    return os;
}

#endif