#include "nmr/StringUtils.h"
#include <cassert>
#include <iostream>
using namespace std;
using namespace nmr;
/**
 * @brief Unit tests for nmr::StringUtils
 * Test coverage:
 * - Punctuation removal (basic cases)
 * - Edge cases (empty string, all punctuation, no punctuation)
 */
int main() {
    // Test 1: Basic punctuation removal
    string test1 = "Hello, C++ World!";
    string result1 = nmr::StringUtils::removePunctuation(test1);
    assert(result1 == "Hello C++ World" && "Basic punctuation removal failed");
    cout << "Test 1 (Basic Punctuation): PASSED\n";
    cout << "Result: \"" << result1 << "\"\n";

    // Test 2: All punctuation
    string test2 = "!!!,,,;;;???";
    string result2 = nmr::StringUtils::removePunctuation(test2);
    assert(result2.empty() && "All punctuation removal failed");
    cout << "Test 2 (All Punctuation): PASSED\n";
    cout << "Result: \"" << result2 << "\"\n";

    // Test 3: No punctuation
    string test3 = "Hello World 123";
    string result3 = nmr::StringUtils::removePunctuation(test3);
    assert(result3 == test3 && "No punctuation preservation failed");
    cout << "Test 3 (No Punctuation): PASSED\n";
    cout << "Result: \"" << result3 << "\"\n";

    // Test 4: Mixed punctuation
    string test4 = "(Hello) [World] {C++}!";
    string result4 = nmr::StringUtils::removePunctuation(test4);
    assert(result4 == "Hello World C++" && "Mixed punctuation removal failed");
    cout << "Test 4 (Mixed Punctuation): PASSED\n";
    cout << "Result: \"" << result4 << "\"\n";

    string test5 = "hello world,cpp.best language!";
    Vector<size_t> loc = nmr::StringUtils::getDelimiterLocation(test5, " !,.");
    for (size_t idx : loc)
        cout << "[" << test5[idx] << "]" << ",";
    cout << "\n";

    string test6 = "hello world,cpp.best language!";
    nmr::Vector<string> substr;
    size_t count  = nmr::StringUtils::splitToStringArray(test6, " !,", substr);
    for (const string& str : substr)
        cout << "[" << str << "]" << ",";
    cout << "count: " << count << "\n";
    return 0;
}