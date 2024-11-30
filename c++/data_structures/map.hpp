#ifndef MAP_H
#define MAP_H

#include <string>
#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

template <typename T>
class Map {
private:
    struct KeyVal {
        string key;
        T value;
        KeyVal* next;

        KeyVal(string k, T v) : key(k), value(v), next(nullptr) {}
    };

    KeyVal** data;// указатель на массив указателей
    int cap;
    int len;
    double loadFactor;

public:
    Map() {
        cap = 16;
        len = 0;
        loadFactor = 0.50;

        data = new KeyVal*[cap];

        for (int i = 0; i < cap; i++) {
            data[i] = nullptr;
        }
    }

    KeyVal** getData() const {
        return data;
    }

    int getLen() const {
        return len;
    }

    int getCap() const {
        return cap;
    }

    uint32_t hash(string key) const {
        uint32_t hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash;
    }

    void put(string key, T value) {
        if (static_cast<double>(len) / cap >= loadFactor) {
            rehash(cap * 2);
        }

        uint32_t index = hash(key) % cap; //Вычисляется индекс бакета с помощью хэш-функции

        if (data[index] == nullptr) { // бакета нет
            data[index] = new KeyVal(key, value);// создается новый элемент
        } else { // бакет есть -> добавляем в него
            KeyVal* current = data[index];
            if (current->key == key) {
                current->value = value; // обновление значения
                return;
            }

            while (current->next != nullptr) {
                if (current->key == key) {
                    current->value = value;
                    return;
                }
                current = current->next;
            }

            current->next = new KeyVal(key, value); //новый элемент
        }

        len++;
    }

    T get(string key) const {
        uint32_t index = hash(key) % cap;

        KeyVal* current = data[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        throw runtime_error("Key not found");
    }

    void remove(string key) {
        uint32_t index = hash(key) % cap;

        KeyVal* prev = nullptr;
        KeyVal* current = data[index];

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    data[index] = current->next;
                    delete current;
                    len--;
                    return;
                } else {
                    prev = current->next;
                    delete current;
                    len--;
                    return;
                }
            }
            prev = current;
            current = current->next;
        }

        throw runtime_error("Key not found");
    }

    void rehash(int newcap) {
        KeyVal** newMap = new KeyVal*[newcap]; // новый массив бакетов увеличенного размера

        for (int i = 0; i < newcap; i++) {
            newMap[i] = nullptr;
        }

        for (int i = 0; i < cap; i++) {
            KeyVal* current = data[i];
            while (current != nullptr) {
                KeyVal* next = current->next;
                uint32_t newIndex = hash(current->key) % newcap;
                
                if (newMap[newIndex] == nullptr) { // бакета нет
                    current->next = nullptr;
                    newMap[newIndex] = current;
                } else { // бакет есть -> добавляем в него
                    KeyVal* currentNewMap = newMap[newIndex];

                    while (currentNewMap->next != nullptr) {
                        currentNewMap = currentNewMap->next;
                    }
                    current->next = nullptr;
                    currentNewMap->next = current;
                }
                current = next;
            }
        }

        delete[] data;
        data = newMap;
        cap = newcap;
    }

    string join() {
        vector<pair<string, int>> sorted_items;

        for (int i = 0; i < cap; i++) {
            KeyVal* current = data[i];
            while (current != nullptr) {
                sorted_items.push_back({current->key, current->value});
                current = current->next;
            }
        }

        sort(sorted_items.begin(), sorted_items.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.first < b.first; 
        });

        string result = "";
        for (const auto& pair : sorted_items) {
            result += pair.first + "," + std::to_string(pair.second) + ";";
        }

        if (!result.empty()) {
            result = result.substr(0, result.size() - 1);
        }

        return result;
    }

    void serializeToBinary(const string& filename) const {
        ofstream file(filename, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Could not open file for writing");
        }

        // Сохраняем количество элементов и емкость
        file.write(reinterpret_cast<const char*>(&len), sizeof(len));
        file.write(reinterpret_cast<const char*>(&cap), sizeof(cap));

        for (int i = 0; i < cap; i++) {
            KeyVal* current = data[i];
            while (current != nullptr) {
                size_t keySize = current->key.size();
                file.write(reinterpret_cast<const char*>(&keySize), sizeof(keySize));
                file.write(current->key.c_str(), keySize);
                file.write(reinterpret_cast<const char*>(&current->value), sizeof(T));
                current = current->next;
            }
        }

        file.close();
    }

    // Метод десериализации
    void deserializeFromBinary(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Could not open file for reading");
        }

        // Очищаем текущую карту
        for (int i = 0; i < cap; i++) {
            KeyVal* current = data[i];
            while (current != nullptr) {
                KeyVal* next = current->next;
                delete current;
                current = next;
            }
            data[i] = nullptr;
        }

        len = 0;

        // Считываем количество элементов и емкость
        int newLen, newCap;
        file.read(reinterpret_cast<char*>(&newLen), sizeof(newLen));
        file.read(reinterpret_cast<char*>(&newCap), sizeof(newCap));

        cap = newCap;
        len = 0;
        delete[] data;
        data = new KeyVal*[cap];
        for (int i = 0; i < cap; i++) {
            data[i] = nullptr;
        }

        // Считываем элементы
        for (int i = 0; i < newLen; i++) {
            size_t keySize;
            file.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));
            string key(keySize, ' ');
            file.read(&key[0], keySize);

            T value;
            file.read(reinterpret_cast<char*>(&value), sizeof(T));
            put(key, value);
        }

        file.close();
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Map<T>& map) {
    auto data = map.getData();
    for (int i = 0; i < map.getCap(); i++) {
        if (data[i] != nullptr) {
            auto current = data[i];
            os << i << ": ";
            while (current!= nullptr) {
                os << current->key << " - " << current->value << ", ";
                current = current->next;
            }
            os << endl;
        }
    }
    return os;
}

#endif
