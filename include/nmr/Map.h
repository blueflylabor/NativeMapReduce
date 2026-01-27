#ifndef NMR_MAP_H
#define NMR_MAP_H

#include <string>
#include <vector>
#include <cstddef>
#include <iostream>
using namespace std;
namespace nmr {
    template <typename T>
    class Map {
        private:
            T* data;
            size_t size;
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            explicit iterator(T* data = nullptr ,size_t size = 0) : data(data), size(size) {}
    };
}