#ifndef NMR_MAP_H
#define NMR_MAP_H

#include <vector>
#include <cstddef>
#include <iostream>
using namespace std;

namespace nmr {
    template <typename K, typename V>
    struct Pair{
        K key;
        V value;
    };
    template <typename K, typename V>
    class Map {
    private:
        Pair<K,V>* data;
        size_t size;
        size_t capacity;
        int findIndex(const K& key) const{
            for (size_t i = 0; i < size; ++i) {
                if (data[i].key == key)
                    return static_cast<int>(i);
            }
            return -1;
        }

    public:
        Map() : size(0), capacity(2) {
            data = new Pair<K,V>[capacity];
        }

        ~Map() {
            delete[] data;
        }

        void put(const K& key, const V& value) {
            int index = findIndex(key);
            if (index != -1) {
                data[index].value = value;
                return;
            }
            if (size == capacity) {
                capacity *= 2;
                Pair<K,V>* newData = new Pair<K,V>[capacity];
                for (size_t i = 0; i < size; ++i)
                    newData[i] = data[i];
                delete[] data;
                data = newData;
            }
            data[size++] = {key, value};
        }
        // 原错误get函数
        V& get(const K& key) {
            int index = findIndex(key);
            if (index == -1)
                    throw std::runtime_error("Key not found");
            return data[index].value;
        }

        V& operator[](const K& key) {
            int index = findIndex(key);
            if (index == -1)
                return data[index].value;
            if (size == capacity) {
                capacity *= 2;
                Pair<K,V>* newData = new Pair<K,V>[capacity];
                for (size_t i = 0; i < size; ++i)
                    newData[i] = data[i];
                delete[] data;
                data = newData;
            }
            data[index].key = key;
            data[size].value = V();
            size++;
            return data[size - 1].value;
        }

        Map(Map&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
            other.data = nullptr;
            other.capacity = 0;
            other.size = 0;
        }
        Map(const Map&) = delete;
        Map& operator=(const Map&) = delete;
        Map& operator=(Map&&) = delete;
    };
}
#endif