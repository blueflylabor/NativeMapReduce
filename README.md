NativeMapReduce: Core Utility Library

Overview

This project provides a lightweight, standard-compliant C++ utility library tailored for native map-reduce tasks. It includes a generic dynamic array implementation (`Vector`) with iterators and a string processing utility class (`StringUtils`) for common string operations like delimiter location detection and string splitting. The library emphasizes memory safety, efficiency, and compatibility with modern C++ standards (C++11 and above).

Features

- Generic Vector Class: Dynamic resizing, deep copy/move semantics, bounds checking, and standard-compliant iterators (supports range-based for loops).

- String Utilities: Delimiter position detection and string splitting with support for custom delimiter sets.

- Memory Safety: Automatic memory management, no raw pointer leaks, and exception-based error handling (avoids abrupt program termination).

- Extensibility: Template-based design allows `Vector` to work with any data type (int, size_t, std::string, etc.).

- Function Overloading: Multiple overloads for utility functions to adapt to different input/output requirements.

Prerequisites

- C++ Compiler: GCC 5.4+, Clang 3.8+, or MSVC 2015+ (supports C++11)

- Build System: CMake 3.10+

- Dependencies: No external dependencies (uses only C++ Standard Library)

Installation

1. Clone the Repository

git clone https://github.com/your-username/NativeMapReduce.git
cd NativeMapReduce

2. Build with CMake

mkdir build && cd build
cmake ..
make -j$(nproc)  # Use `make -jN` where N is your number of CPU cores
make install     # Optional: Install to system include/lib directories

Usage Examples

1. Vector Class Usage

#include "nmr/Vector.h"
#include <iostream>

int main() {
// Initialize a Vector of size_t
nmr::Vector<size_t> vec;
vec.push_back(5);
vec.push_back(11);
vec.push_back(15);

    // Range-based for loop (uses iterators)
    std::cout << "Vector elements: ";
    for (size_t val : vec) {
        std::cout << val << " ";  // Output: 5 11 15
    }
    std::cout << std::endl;

    // Bounds-checked access
    try {
        std::cout << "Element at index 1: " << vec.at(1) << std::endl;  // Output: 11
        vec.at(5);  // Throws std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

2. StringUtils Usage

#include "nmr/StringUtils.h"
#include "nmr/Vector.h"
#include <iostream>
#include <string>

int main() {
std::string test_str = "hello,world.cpp.best!language";
std::string delimiters = "!,. ";
nmr::Vector<std::string> words;

    // Split string by delimiters
    size_t count = nmr::StringUtils::splitToStringArray(test_str, delimiters, words);

    // Print results
    std::cout << "Split results (" << count << " elements): ";
    for (const auto& word : words) {
        std::cout << "[" << word << "],";  // Output: [hello],[world],[cpp],[best],[language],
    }
    std::cout << std::endl;

    // Get delimiter locations
    nmr::Vector<size_t> locations;
    nmr::Vector<char> delimiter_chars;
    nmr::StringUtils::getDelimiterLocation(test_str, delimiters, locations, delimiter_chars);

    std::cout << "Delimiter locations: ";
    for (size_t i = 0; i < locations.getSize(); ++i) {
        std::cout << locations[i] << ":" << delimiter_chars[i] << " ";  // Output: 5:, 11:. 15:. 20:!
    }
    std::cout << std::endl;

    return 0;
}

API Reference

nmr::Vector<T>

Constructors & Destructor

- Vector(): Default constructor (empty vector).

- explicit Vector(size_t s): Constructs a vector with s value-initialized elements.

- Vector(const T* arr, size_t arr_size): Constructs a vector from a C-style array.

- Vector(const Vector& other): Copy constructor (deep copy).

- Vector(Vector&& other) noexcept: Move constructor (zero-copy resource transfer).

- ~Vector() noexcept: Destructor (releases dynamic memory).

Element Access

- T& operator[](size_t index): Unchecked subscript access (modifiable).

- const T& operator[](size_t index) const: Unchecked subscript access (read-only).

- T& at(size_t index): Bounds-checked access (throws std::out_of_range if invalid).

- const T& at(size_t index) const: Const bounds-checked access.

Iterators

- iterator begin() noexcept: Returns iterator to the first element.

- const_iterator begin() const noexcept: Returns const iterator to the first element.

- const_iterator cbegin() const noexcept: Explicit const iterator to the first element.

- iterator end() noexcept: Returns iterator to the element past the last element.

- const_iterator end() const noexcept: Returns const iterator to the element past the last element.

- const_iterator cend() const noexcept: Explicit const iterator to the element past the last element.

Modifiers

- void push_back(const T&amp; value): Adds an element to the end (dynamic resizing).

- void clear() noexcept: Clears all elements and releases memory.

Capacity

- size_t getSize() const noexcept: Returns the number of elements.

- bool isEmpty() const noexcept: Returns true if the vector is empty.

nmr::StringUtils

Static Methods

- static void getDelimiterLocation(const std::string& str, const std::string& delimiter, Vector<size_t>& locations, Vector<char>& delimiters): Detects positions of all delimiter characters instr; stores positions in locations and corresponding delimiter characters indelimiters.

- static void getDelimiterLocation(const std::string& str, const std::string& delimiter, Vector<size_t>& locations): Overload; only stores delimiter positions (discards delimiter characters).

- static size_t splitToStringArray(const std::string& str, const std::string& delimiter, Vector<std::string>& out_words): Splits str by delimiters; stores non-empty substrings inout_words; returns the number of substrings.

Testing

Unit tests are located in the test/ directory. To run tests after building:

cd build
./test/test_Vector       # Test Vector class functionality
./test/test_StringUtils  # Test StringUtils functionality

Error Handling

- Bounds checking for Vector access throws std::out_of_range (instead of aborting the program).

- All dynamic memory operations are wrapped in exception-safe logic to prevent leaks.

- Empty input handling (empty strings, empty delimiters) returns valid empty results instead of errors.

Best Practices

- Always use at() instead ofoperator[] for bounds-checked access in critical code.

- Use move semantics (std::move) with Vector to avoid unnecessary copies for large datasets.

- Clear output containers (out_words.clear()) before passing to splitToStringArray (though the function does this internally).

- Use const_iterator (or cbegin()/cend()) for read-only traversal to enforce const-correctness.

License

This project is licensed under the MIT License - see the LICENSE file for details.

Contact

For questions or contributions, please contact: [Your Name] <your.email@example.com>
