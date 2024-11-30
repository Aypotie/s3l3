#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "dlist.hpp"

using namespace std;

template <typename T>
class Queue {
private:
    Dlist<T> list;

public:
    Queue() {}
    
    Dlist<T> data() const {
        return list;
    }

    int size() const {
        return list.size();
    }

    void enqueue(const T& val) {
        list.pushBack(val);
    }

    T dequeue() {
        if (size() == 0) {
            throw runtime_error("Queue is empty");
        }

        T dequeued = list.getHead()->value;
        list.removeForward();

        return dequeued;
    }

    void serializeToBinary(const string& filename) const {
        list.serializeToBinary(filename);
    }

    void deserializeFromBinary(const string& filename) {
        list.deserializeFromBinary(filename);
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Queue<T>& queue) {
    os << queue.data() << endl;
    return os;
}

#endif
