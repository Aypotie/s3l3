#include "../data_structures/avl.hpp"
#include "../data_structures/vector.hpp"
#include "../data_structures/slist.hpp"
#include "../data_structures/dlist.hpp"
#include "../data_structures/map.hpp"
#include "../data_structures/stack.hpp"
#include "../data_structures/queue.hpp"

#include <iostream>

using namespace std;

void vect() {
    Vector<int> vec;
    vec.pushBack(1);
    vec.pushBack(2);
    vec.pushBack(3);

    vec.serializeToBinary("vector.bin");
    Vector<int> vecFromBinary;
    vecFromBinary.deserializeFromBinary("vector.bin");
    cout << "Binary deserialized: " << vecFromBinary;
}

void slis() {
    SList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);

    list.serializeToBinary("slist.bin");
    cout << "List serialized to binary file." << endl;

    SList<int> newList;
    newList.deserializeFromBinary("slist.bin");
    cout << "Deserialized list: " << newList << endl;
}

void stac() {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.serializeToBinary("stack.bin");
    cout << "Stack serialized to binary file." << endl;

    Stack<int> newStack;
    newStack.deserializeFromBinary("stack.bin");
    cout << "Deserialized stack: " << newStack << endl;
}

void dlis() {
    Dlist<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);

    list.serializeToBinary("dlist.bin");
    cout << "List serialized to binary file." << endl;

    Dlist<int> newList;
    newList.deserializeFromBinary("dlist.bin");
    cout << "Deserialized list: " << newList << endl;
}

void queu() {
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    queue.serializeToBinary("queue.bin");
    cout << "Queue serialized to binary file." << endl;

    Queue<int> newQueue;
    newQueue.deserializeFromBinary("queue.bin");
    cout << "Deserialized queue: " << newQueue << endl;
}

void ma() {
    Map<int> map;

    map.put("key1", 10);
    map.put("key2", 20);
    map.put("key3", 30);

    map.serializeToBinary("map.bin");
    cout << "Map serialized to binary file." << endl;

    Map<int> newMap;
    newMap.deserializeFromBinary("map.bin");

    cout << "Deserialized Map: " << newMap;
}

void tre() {
    AVLTree tree;
    tree.insertNum(10);
    tree.insertNum(5);
    tree.insertNum(15);
    tree.insertNum(2);

    cout << "Original Tree:" << endl;
    cout << tree;

    // Сериализация в бинарный файл
    tree.serializeBinary("tree.bin");

    // Десериализация из бинарного файла
    AVLTree newTree;
    newTree.unserializeBinary("tree.bin");

    cout << "Deserialized Tree:" << endl;
    cout << newTree;
}

int main() {
    tre();
    return 0;
}