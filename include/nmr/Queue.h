#ifndef NMR_QUEUE_H
#define NMR_QUEUE_H

#include <string>
#include <iostream>
#include <stdexcept>

namespace nmr {

/**
 * @brief Generic circular queue implementation (template class)
 * @tparam T Type of elements stored in the queue
 * 
 * Key Features:
 * - Circular buffer design (reuses empty space efficiently)
 * - Deep copy support (copy constructor + assignment operator)
 * - Safe error handling (exceptions instead of program crash)
 * - Helper methods for state checking (size/is_empty/is_full)
 * - pop_all() to clear and print all elements
 */
template<typename T>
class Queue {
private:
    // Member declaration order (critical for constructor initializer list)
    T* data;          // Dynamic array for queue elements
    size_t front;     // Index of front element (next to pop)
    size_t rear;      // Index of rear position (next to push)
    size_t capacity;  // Maximum number of elements
    size_t count;     // Current number of elements

public:
    /**
     * @brief Constructor: Initialize queue with specified capacity
     * @param cap Maximum capacity of the queue
     * @throw std::invalid_argument If capacity is 0
     */
    Queue(size_t cap) : front(0), rear(0), capacity(cap), count(0) {
        if (cap == 0) {
            throw std::invalid_argument("Queue capacity cannot be 0");
        }
        data = new T[capacity];
    }

    /**
     * @brief Destructor: Release dynamic memory
     */
    ~Queue() {
        delete[] data;
    }

    /**
     * @brief Copy constructor: Deep copy of another queue
     * @param other Queue to copy from
     */
    Queue(const Queue& other) : 
        front(other.front), 
        rear(other.rear), 
        capacity(other.capacity), 
        count(other.count) 
    {
        data = new T[capacity];
        // Copy all elements (preserve circular buffer state)
        for (size_t i = 0; i < capacity; ++i) {
            data[i] = other.data[i];
        }
    }

    /**
     * @brief Push element to the rear of the queue
     * @param val Element to push
     * @note Prints error message if queue is full (no exception throw)
     */
    void push(T val) {
        if (count == capacity) {
            std::cerr << "[Queue Error] Push failed: Queue is full (capacity=" << capacity << ")" << std::endl;
            return;
        }
        data[rear] = val;
        rear = (rear + 1) % capacity; // Circular increment
        count++;
    }

    /**
     * @brief Pop element from the front of the queue
     * @return Front element of the queue
     * @throw std::underflow_error If queue is empty (safer than exit(1))
     */
    T pop() {
        if (count == 0) {
            throw std::underflow_error("Queue is empty - cannot pop");
        }
        T val = data[front];
        front = (front + 1) % capacity; // Circular increment
        count--;
        return val;
    }

    /**
     * @brief Pop and print all elements (clears the queue)
     * @note Prints warning if queue is empty
     */
    void pop_all() {
        if (count == 0) {
            std::cerr << "[Queue Warning] pop_all failed: Queue is empty" << std::endl;
            return;
        }
        size_t current_count = count;
        for (size_t i = 0; i < current_count; ++i) {
            std::cout << pop() << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Assignment operator: Deep copy of another queue
     * @param other Queue to assign from
     * @return Reference to this queue (chain assignment support)
     */
    Queue<T>& operator=(const Queue<T>& other) {
        // Self-assignment check
        if (this == &other) {
            return *this;
        }

        // Release current memory
        delete[] data;

        // Copy state from other queue (match member declaration order)
        front = other.front;
        rear = other.rear;
        capacity = other.capacity;
        count = other.count;

        // Allocate new memory and copy elements
        data = new T[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            data[i] = other.data[i];
        }

        return *this;
    }

    // ------------------------------
    // Helper methods (for usability)
    // ------------------------------
    /**
     * @brief Get current number of elements in queue
     * @return Current count
     */
    size_t size() const {
        return count;
    }

    /**
     * @brief Check if queue is empty
     * @return true if empty, false otherwise
     */
    bool is_empty() const {
        return count == 0;
    }

    /**
     * @brief Check if queue is full
     * @return true if full, false otherwise
     */
    bool is_full() const {
        return count == capacity;
    }

    /**
     * @brief Get queue capacity
     * @return Maximum number of elements
     */
    size_t get_capacity() const {
        return capacity;
    }
};

} // namespace nmr

#endif // NMR_QUEUE_H