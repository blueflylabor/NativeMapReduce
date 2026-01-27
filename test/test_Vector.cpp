#include "nmr/Vector.h"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    // Test 1: Int vector (basic functionality)
    nmr::Vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    assert(v1.getSize() == 3 && "Test 1 failed: Size mismatch");
    assert(v1[0] == 10 && v1[1] == 20 && v1[2] == 30 && "Test 1 failed: Element mismatch");
    std::cout << "Test 1 (Int Vector Basic) - PASSED" << std::endl;

    // Test 2: Size_t vector (for StringUtils)
    nmr::Vector<size_t> v2;
    v2.push_back(0);
    v2.push_back(12);
    assert(v2.getSize() == 2 && "Test 2 failed: Size mismatch");
    assert(v2.at(0) == 0 && v2.at(1) == 12 && "Test 2 failed: Element mismatch");
    std::cout << "Test 2 (Size_t Vector) - PASSED" << std::endl;

    // Test 3: String vector (generic type support)
    nmr::Vector<std::string> v3;
    v3.push_back("Hello");
    v3.push_back("World");
    assert(v3.getSize() == 2 && "Test 3 failed: Size mismatch");
    assert(v3[0] == "Hello" && v3[1] == "World" && "Test 3 failed: Element mismatch");
    std::cout << "Test 3 (String Vector) - PASSED" << std::endl;

    // Test 4: Bounds check (exception)
    try {
        v1[5]; // Out of bounds
        assert(false && "Test 4 failed: Should throw exception");
    } catch (const std::out_of_range& e) {
        std::cout << "Test 4 - Expected exception: " << e.what() << std::endl;
        assert(true);
        std::cout << "Test 4 (Bounds Check) - PASSED" << std::endl;
    }

    // Test 5: Copy constructor
    nmr::Vector<int> v4 = v1;
    assert(v4.getSize() == 3 && "Test 5 failed: Copy size mismatch");
    v4[0] = 100; // Modify copy (should not affect original)
    assert(v1[0] == 10 && "Test 5 failed: Shallow copy issue");
    std::cout << "Test 5 (Copy Constructor) - PASSED" << std::endl;

    // Test 6: Move constructor
    nmr::Vector<int> v5 = std::move(v1);
    assert(v5.getSize() == 3 && "Test 6 failed: Move size mismatch");
    assert(v1.isEmpty() && "Test 6 failed: Source vector not nullified");
    std::cout << "Test 6 (Move Constructor) - PASSED" << std::endl;

    // Test 7: Clear method
    v5.clear();
    assert(v5.isEmpty() && "Test 7 failed: Clear not working");
    std::cout << "Test 7 (Clear Method) - PASSED" << std::endl;

    std::cout << "\n✅ All Vector tests passed successfully!" << std::endl;
    return 0;
}