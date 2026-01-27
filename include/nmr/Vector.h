#ifndef NMR_VECTOR_H
#define NMR_VECTOR_H

#include <iostream>
#include <stdexcept>
#include <cstddef> // for size_t
#include <iterator> // for std::iterator_traits

namespace nmr {

/**
 * @brief Generic dynamic array (vector) implementation (template class)
 * @tparam T Type of elements stored in the vector
 *
 * Key Features:
 * - Dynamic resizing (push_back auto-reallocates)
 * - Deep copy (copy constructor/assignment operator)
 * - Move semantics (zero-copy resource transfer)
 * - Bounds checking (throws exceptions instead of exit)
 * - Support for const/non-const element access
 * - Standard-compliant iterators (support range-based for loops)
 */
template <typename T>
class Vector {
private:
    T* data;          // Dynamic array to store elements
    size_t size;      // Current number of elements

public:
    // ------------------------------
    // Iterator Definitions (C++ Standard Compliant)
    // ------------------------------
    /**
     * @brief Non-const iterator for Vector
     */
    class iterator {
    private:
        T* ptr; // Pointer to current element
    public:
        // Iterator traits (for STL compatibility)
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /**
         * @brief Constructor: initialize with pointer
         */
        explicit iterator(T* p = nullptr) : ptr(p) {}

        /**
         * @brief Dereference operator: access element
         */
        reference operator*() const { return *ptr; }

        /**
         * @brief Arrow operator: access member of element
         */
        pointer operator->() const { return ptr; }

        /**
         * @brief Pre-increment: move to next element
         */
        iterator& operator++() {
            ++ptr;
            return *this;
        }

        /**
         * @brief Post-increment: move to next element (return old value)
         */
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr;
            return temp;
        }

        /**
         * @brief Pre-decrement: move to previous element
         */
        iterator& operator--() {
            --ptr;
            return *this;
        }

        /**
         * @brief Post-decrement: move to previous element (return old value)
         */
        iterator operator--(int) {
            iterator temp = *this;
            --ptr;
            return temp;
        }

        /**
         * @brief Addition operator: move forward by n elements
         */
        iterator operator+(difference_type n) const {
            return iterator(ptr + n);
        }

        /**
         * @brief Subtraction operator: move backward by n elements
         */
        iterator operator-(difference_type n) const {
            return iterator(ptr - n);
        }

        /**
         * @brief Difference operator: get distance between two iterators
         */
        difference_type operator-(const iterator& other) const {
            return ptr - other.ptr;
        }

        /**
         * @brief Compound assignment: move forward by n elements
         */
        iterator& operator+=(difference_type n) {
            ptr += n;
            return *this;
        }

        /**
         * @brief Compound assignment: move backward by n elements
         */
        iterator& operator-=(difference_type n) {
            ptr -= n;
            return *this;
        }

        /**
         * @brief Subscript operator: access element at offset
         */
        reference operator[](difference_type n) const {
            return *(ptr + n);
        }

        /**
         * @brief Equality comparison
         */
        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        /**
         * @brief Inequality comparison
         */
        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

        /**
         * @brief Less than comparison
         */
        bool operator<(const iterator& other) const {
            return ptr < other.ptr;
        }

        /**
         * @brief Greater than comparison
         */
        bool operator>(const iterator& other) const {
            return ptr > other.ptr;
        }

        /**
         * @brief Less than or equal comparison
         */
        bool operator<=(const iterator& other) const {
            return ptr <= other.ptr;
        }

        /**
         * @brief Greater than or equal comparison
         */
        bool operator>=(const iterator& other) const {
            return ptr >= other.ptr;
        }
    };

    /**
     * @brief Const iterator for Vector (read-only access)
     */
    class const_iterator {
    private:
        const T* ptr; // Const pointer to current element
    public:
        // Iterator traits (for STL compatibility)
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        /**
         * @brief Constructor: initialize with const pointer
         */
        explicit const_iterator(const T* p = nullptr) : ptr(p) {}

        /**
         * @brief Conversion from non-const iterator to const iterator
         */
        const_iterator(const iterator& it) : ptr(it.operator->()) {}

        /**
         * @brief Dereference operator: read-only access to element
         */
        reference operator*() const { return *ptr; }

        /**
         * @brief Arrow operator: read-only access to member of element
         */
        pointer operator->() const { return ptr; }

        /**
         * @brief Pre-increment: move to next element
         */
        const_iterator& operator++() {
            ++ptr;
            return *this;
        }

        /**
         * @brief Post-increment: move to next element (return old value)
         */
        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++ptr;
            return temp;
        }

        /**
         * @brief Pre-decrement: move to previous element
         */
        const_iterator& operator--() {
            --ptr;
            return *this;
        }

        /**
         * @brief Post-decrement: move to previous element (return old value)
         */
        const_iterator operator--(int) {
            const_iterator temp = *this;
            --ptr;
            return temp;
        }

        /**
         * @brief Addition operator: move forward by n elements
         */
        const_iterator operator+(difference_type n) const {
            return const_iterator(ptr + n);
        }

        /**
         * @brief Subtraction operator: move backward by n elements
         */
        const_iterator operator-(difference_type n) const {
            return const_iterator(ptr - n);
        }

        /**
         * @brief Difference operator: get distance between two iterators
         */
        difference_type operator-(const const_iterator& other) const {
            return ptr - other.ptr;
        }

        /**
         * @brief Compound assignment: move forward by n elements
         */
        const_iterator& operator+=(difference_type n) {
            ptr += n;
            return *this;
        }

        /**
         * @brief Compound assignment: move backward by n elements
         */
        const_iterator& operator-=(difference_type n) {
            ptr -= n;
            return *this;
        }

        /**
         * @brief Subscript operator: read-only access to element at offset
         */
        reference operator[](difference_type n) const {
            return *(ptr + n);
        }

        /**
         * @brief Equality comparison
         */
        bool operator==(const const_iterator& other) const {
            return ptr == other.ptr;
        }

        /**
         * @brief Inequality comparison
         */
        bool operator!=(const const_iterator& other) const {
            return ptr != other.ptr;
        }

        /**
         * @brief Less than comparison
         */
        bool operator<(const const_iterator& other) const {
            return ptr < other.ptr;
        }

        /**
         * @brief Greater than comparison
         */
        bool operator>(const const_iterator& other) const {
            return ptr > other.ptr;
        }

        /**
         * @brief Less than or equal comparison
         */
        bool operator<=(const const_iterator& other) const {
            return ptr <= other.ptr;
        }

        /**
         * @brief Greater than or equal comparison
         */
        bool operator>=(const const_iterator& other) const {
            return ptr >= other.ptr;
        }
    };

    // ------------------------------
    // Iterator Access Methods
    // ------------------------------
    /**
     * @brief Get iterator to the first element
     */
    iterator begin() noexcept {
        return iterator(data);
    }

    /**
     * @brief Get const iterator to the first element
     */
    const_iterator begin() const noexcept {
        return const_iterator(data);
    }

    /**
     * @brief Get const iterator to the first element (explicit const version)
     */
    const_iterator cbegin() const noexcept {
        return const_iterator(data);
    }

    /**
     * @brief Get iterator to the element past the last element
     */
    iterator end() noexcept {
        return iterator(data + size);
    }

    /**
     * @brief Get const iterator to the element past the last element
     */
    const_iterator end() const noexcept {
        return const_iterator(data + size);
    }

    /**
     * @brief Get const iterator to the element past the last element (explicit const version)
     */
    const_iterator cend() const noexcept {
        return const_iterator(data + size);
    }

    // ------------------------------
    // Constructors & Destructor (保持原有代码不变)
    // ------------------------------
    Vector() noexcept : data(nullptr), size(0) {}
    explicit Vector(size_t s);
    Vector(const T* arr, size_t arr_size);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector() noexcept;

    // ------------------------------
    // Assignment Operators (保持原有代码不变)
    // ------------------------------
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    // ------------------------------
    // Element Access (保持原有代码不变)
    // ------------------------------
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& at(size_t index);
    const T& at(size_t index) const;

    // ------------------------------
    // Capacity & Data Access (保持原有代码不变)
    // ------------------------------
    size_t getSize() const noexcept { return size; }
    bool isEmpty() const noexcept { return size == 0; }
    const T* getData() const noexcept { return data; }

    // ------------------------------
    // Modifiers (保持原有代码不变)
    // ------------------------------
    void push_back(const T& value);
    void clear() noexcept;

    // ------------------------------
    // Utility (保持原有代码不变)
    // ------------------------------
    void show() const;
};

// ------------------------------
// Template Implementation (保持原有代码不变，仅补充迭代器相关无修改)
// ------------------------------

// Parameterized constructor
template <typename T>
Vector<T>::Vector(size_t s) : size(s) {
    if (s == 0) {
        data = nullptr;
        return;
    }
    data = new T[s]();
}

// Constructor from C-style array
template <typename T>
Vector<T>::Vector(const T* arr, size_t arr_size) : size(arr_size) {
    if (arr_size == 0 || arr == nullptr) {
        data = nullptr;
        return;
    }
    data = new T[arr_size];
    for (size_t i = 0; i < arr_size; ++i) {
        data[i] = arr[i];
    }
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& other) : size(other.size) {
    if (other.size == 0) {
        data = nullptr;
        return;
    }
    data = new T[other.size];
    for (size_t i = 0; i < other.size; ++i) {
        data[i] = other.data[i];
    }
}

// Move constructor
template <typename T>
Vector<T>::Vector(Vector&& other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

// Destructor
template <typename T>
Vector<T>::~Vector() noexcept {
    delete[] data;
    data = nullptr;
    size = 0;
}

// Copy assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }
    delete[] data;
    size = other.size;
    if (other.size == 0) {
        data = nullptr;
        return *this;
    }
    data = new T[other.size];
    for (size_t i = 0; i < other.size; ++i) {
        data[i] = other.data[i];
    }
    return *this;
}

// Move assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete[] data;
    data = other.data;
    size = other.size;
    other.data = nullptr;
    other.size = 0;
    return *this;
}

// Non-const subscript operator
template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Vector subscript out of range: index = " + std::to_string(index) + ", size = " + std::to_string(size));
    }
    return data[index];
}

// Const subscript operator
template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Vector subscript out of range: index = " + std::to_string(index) + ", size = " + std::to_string(size));
    }
    return data[index];
}

// Safe at() method (non-const)
template <typename T>
T& Vector<T>::at(size_t index) {
    return operator[](index);
}

// Safe at() method (const)
template <typename T>
const T& Vector<T>::at(size_t index) const {
    return operator[](index);
}

// Push back (dynamic resize)
template <typename T>
void Vector<T>::push_back(const T& value) {
    T* new_data = new T[size + 1];
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    new_data[size] = value;
    delete[] data;
    data = new_data;
    size++;
}

// Clear all elements
template <typename T>
void Vector<T>::clear() noexcept {
    delete[] data;
    data = nullptr;
    size = 0;
}

// Print elements
template <typename T>
void Vector<T>::show() const {
    if (size == 0) {
        std::cout << "[Vector] Empty" << std::endl;
        return;
    }
    std::cout << "[Vector] Elements: ";
    for (size_t i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

} // namespace nmr

#endif // NMR_VECTOR_H