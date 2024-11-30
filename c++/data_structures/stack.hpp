#ifndef STACK_H
#define STACK_H

#include "slist.hpp"

template <typename T>
class Stack {
private:
    SList<T> list;

public:
    Stack() {}

    int size() const {
        return list.size();
    }

    SList<T> data() const {
        return list;
    }

    void push(const T& value) {
        list.pushForward(value);
    }

    T pop() {
        if (list.getHead() == nullptr) {
            throw runtime_error("Stack is empty");
        }
        T popped = list.getHead()->value;
        list.removeForward();
        return popped;
    }

    void serializeToBinary(const string& filename) const {
        list.serializeToBinary(filename);
    }

    void deserializeFromBinary(const string& filename) {
        list.deserializeFromBinary(filename);
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Stack<T>& stack) {
    os << stack.data() << endl;
    return os;
}

#endif
