#ifndef NMR_VECTOR_H
#define NMR_VECTOR_H

#include <iostream>
#include <stdexcept>
#include <cstddef> // for size_t

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
 */
template <typename T>
class Vector {
private:
    T* data;          // Dynamic array to store elements
    size_t size;      // Current number of elements

public:
    // ------------------------------
    // Constructors & Destructor
    // ------------------------------
    /**
     * @brief Default constructor: empty vector
     */
    Vector() noexcept : data(nullptr), size(0) {}

    /**
     * @brief Parameterized constructor: vector with specified size
     * @param s Initial size of the vector
     * @note Elements are value-initialized (zero for numeric types)
     */
    explicit Vector(size_t s);

    /**
     * @brief Constructor from C-style array
     * @param arr Source C-style array
     * @param arr_size Size of the source array
     */
    Vector(const T* arr, size_t arr_size);

    /**
     * @brief Copy constructor: deep copy
     * @param other Vector to copy from
     */
    Vector(const Vector& other);

    /**
     * @brief Move constructor: transfer ownership (no copy)
     * @param other Rvalue reference to source vector
     */
    Vector(Vector&& other) noexcept;

    /**
     * @brief Destructor: release dynamic memory
     */
    ~Vector() noexcept;

    // ------------------------------
    // Assignment Operators
    // ------------------------------
    /**
     * @brief Copy assignment operator: deep copy
     * @param other Vector to assign from
     * @return Reference to this vector
     */
    Vector& operator=(const Vector& other);

    /**
     * @brief Move assignment operator: transfer ownership
     * @param other Rvalue reference to source vector
     * @return Reference to this vector
     */
    Vector& operator=(Vector&& other) noexcept;

    // ------------------------------
    // Element Access
    // ------------------------------
    /**
     * @brief Non-const subscript operator: modifiable access
     * @param index Position of element to access
     * @return Reference to element at index
     * @throw std::out_of_range If index >= size
     */
    T& operator[](size_t index);

    /**
     * @brief Const subscript operator: read-only access
     * @param index Position of element to access
     * @return Const reference to element at index
     * @throw std::out_of_range If index >= size
     */
    const T& operator[](size_t index) const;

    /**
     * @brief Safe element access (with bounds check)
     * @param index Position of element to access
     * @return Reference to element at index
     * @throw std::out_of_range If index >= size
     */
    T& at(size_t index);

    /**
     * @brief Const safe element access (with bounds check)
     * @param index Position of element to access
     * @return Const reference to element at index
     * @throw std::out_of_range If index >= size
     */
    const T& at(size_t index) const;

    // ------------------------------
    // Capacity & Data Access
    // ------------------------------
    /**
     * @brief Get current number of elements
     * @return Current size of the vector
     */
    size_t getSize() const noexcept { return size; }

    /**
     * @brief Check if vector is empty
     * @return true if empty, false otherwise
     */
    bool isEmpty() const noexcept { return size == 0; }

    /**
     * @brief Get pointer to underlying data array
     * @return Raw pointer to data (const)
     */
    const T* getData() const noexcept { return data; }

    // ------------------------------
    // Modifiers
    // ------------------------------
    /**
     * @brief Add element to the end of the vector (dynamic resize)
     * @param value Element to add
     */
    void push_back(const T& value);

    /**
     * @brief Clear all elements (release memory)
     */
    void clear() noexcept;

    // ------------------------------
    // Utility
    // ------------------------------
    /**
     * @brief Print all elements to console (space-separated)
     */
    void show() const;
};

// ------------------------------
// Template Implementation (must be in header for template class)
// ------------------------------

// Parameterized constructor
template <typename T>
Vector<T>::Vector(size_t s) : size(s) {
    if (s == 0) {
        data = nullptr;
        return;
    }
    // Value-initialize elements (zero for numeric types)
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
    // Nullify source to avoid double deletion
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
    // Self-assignment check
    if (this == &other) {
        return *this;
    }

    // Release current memory
    delete[] data;

    // Copy state from other
    size = other.size;
    if (other.size == 0) {
        data = nullptr;
        return *this;
    }

    // Allocate new memory and copy elements
    data = new T[other.size];
    for (size_t i = 0; i < other.size; ++i) {
        data[i] = other.data[i];
    }

    return *this;
}

// Move assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    // Self-assignment check
    if (this == &other) {
        return *this;
    }

    // Release current memory
    delete[] data;

    // Transfer ownership
    data = other.data;
    size = other.size;

    // Nullify source
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
    return operator[](index); // Reuse bounds check logic
}

// Safe at() method (const)
template <typename T>
const T& Vector<T>::at(size_t index) const {
    return operator[](index); // Reuse bounds check logic
}

// Push back (dynamic resize)
template <typename T>
void Vector<T>::push_back(const T& value) {
    // Allocate new array with size + 1
    T* new_data = new T[size + 1];

    // Copy existing elements
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }

    // Add new element
    new_data[size] = value;

    // Release old memory and update
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