#include "nmr/Queue.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

int main() {
    // Test 1: Basic push/pop
    nmr::Queue<int> q1(3);
    q1.push(10);
    q1.push(20);
    q1.push(30);
    assert(q1.size() == 3 && "Test 1 failed: Queue size should be 3");
    assert(q1.is_full() == true && "Test 1 failed: Queue should be full");
    
    // Test 2: Push to full queue (error handling)
    q1.push(40); // Should print error
    assert(q1.size() == 3 && "Test 2 failed: Queue size remains 3");
    
    // Test 3: Pop elements
    assert(q1.pop() == 10 && "Test 3 failed: Pop should return 10");
    assert(q1.pop() == 20 && "Test 3 failed: Pop should return 20");
    assert(q1.size() == 1 && "Test 3 failed: Queue size should be 1");
    
    // Test 4: pop_all
    q1.push(40);
    q1.push(50);
    std::cout << "Test 4 - pop_all output: ";
    q1.pop_all(); // Should print "30 40 50 "
    assert(q1.is_empty() == true && "Test 4 failed: Queue should be empty");
    
    // Test 5: Copy constructor
    nmr::Queue<int> q2(2);
    q2.push(100);
    q2.push(200);
    nmr::Queue<int> q3 = q2; // Copy constructor
    assert(q3.pop() == 100 && "Test 5 failed: Copy constructor error");
    assert(q2.size() == 2 && "Test 5 failed: Original queue unchanged");
    
    // Test 6: Assignment operator
    nmr::Queue<int> q4(5);
    q4 = q2;
    assert(q4.size() == 2 && "Test 6 failed: Assignment operator error");
    assert(q4.pop() == 100 && "Test 6 failed: Assignment operator error");
    
    // Test 7: Pop empty queue (exception handling)
    nmr::Queue<int> q5(2);
    try {
        q5.pop();
        assert(false && "Test 7 failed: Should throw exception");
    } catch (const std::underflow_error& e) {
        std::cout << "Test 7 - Expected exception: " << e.what() << std::endl;
        assert(true);
    }

    std::cout << "\nAll Queue tests passed successfully!" << std::endl;
    return 0;
}