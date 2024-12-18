#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Vector {
private:
    T* data;           
    int len;           
    int cap;           
    float loadFactor;  

    void extend() {
        int newCap = cap * 2;
        T* newData = new T[newCap];
        for (int i = 0; i < cap; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        cap = newCap;
    }

public:
    Vector(int initCap = 16, int initLen = 0) {
        cap = initCap;
        len = 0;
        data = new T[cap];
        loadFactor = 0.5;
    }

    int size() const {
        return len;
    }

    int capacity() const {
        return cap;
    }

    void pushBack(T value) {
        if (static_cast<float>(len)/cap >= loadFactor) {
            extend();
        }
        data[len] = value;
        len++;
    }

    void insert(int index, T value) {
        if (static_cast<float>(len)/cap >= loadFactor) {
            extend();
        }
        for (int i = len; i > index; i--) {
            data[i] = data[i - 1]; 
        }
        data[index] = value;
        len++;
    }

    void remove(int index) {
        if (index < 0 || index >= len) {
            throw invalid_argument("invalid index");
        }
        
        for (int i = index; i < len - 1; i++) {
            data[i] = data[i + 1];
        }
        len--;
    }

    void set(int index, T value) {
        if (index < 0 || index >= len) {
            throw invalid_argument("invalid index");
        }
        data[index] = value;
    }

    T get(int index) const {
        if (index < 0 || index >= len) {
            throw invalid_argument("invalid index");
        }

        return data[index];
    }

    // Бинарная сериализация
    void serializeToBinary(string filename) {
        ofstream outFile(filename, ios::binary);
        if (!outFile) {
            throw runtime_error("Unable to open file for binary serialization");
        }
        outFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        outFile.write(reinterpret_cast<const char*>(data), sizeof(T) * len);
        outFile.close();
    }

    void deserializeFromBinary(string filename) {
        ifstream inFile(filename, ios::binary);
        if (!inFile) {
            throw runtime_error("Unable to open file for binary deserialization");
        }
        int newLen;
        inFile.read(reinterpret_cast<char*>(&newLen), sizeof(newLen));
        if (newLen > cap) {
            delete[] data;
            cap = newLen * 2;
            data = new T[cap];
        }
        len = newLen;
        inFile.read(reinterpret_cast<char*>(data), sizeof(T) * len);
        inFile.close();
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Vector<T>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        os << vec.get(i) << ",";
    }
    os << endl;
    return os;
}

#endif
