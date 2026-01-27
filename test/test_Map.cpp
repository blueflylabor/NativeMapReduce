#include <nmr/Map.h>
#include <stdexcept>
#include <string>
#include <cassert>

// Test basic put and get with existing key
void test_put_and_get_exist_key() {
    nmr::Map<std::string, int> map;
    map.put("hello", 1);
    map.put("world", 2);
    map.put("cpp", 3);

    assert(map.get("hello") == 1);
    assert(map.get("world") == 2);
    assert(map.get("cpp") == 3);
}

// Test get non-existent key throws std::runtime_error
void test_get_not_exist_key_throw() {
    nmr::Map<std::string, int> map;
    map.put("hello", 1);

    bool is_throw = false;
    try {
        map.get("java");
    } catch (const std::runtime_error& e) {
        if (std::string(e.what()) == "Key not found") {
            is_throw = true;
        }
    }
    assert(is_throw == true);
}

// Test duplicate put overrides the existing value
void test_put_override_value() {
    nmr::Map<std::string, int> map;
    map.put("hello", 1);
    map.put("hello", 100);

    assert(map.get("hello") == 100);
}

// Test template compatibility with int key type
void test_int_key_type() {
    nmr::Map<int, std::string> map;
    map.put(1, "one");
    map.put(2, "two");

    assert(map.get(1) == "one");
    assert(map.get(2) == "two");
}

// Main test entry: run all test cases
int main() {
    test_put_and_get_exist_key();
    test_get_not_exist_key_throw();
    test_put_override_value();
    test_int_key_type();

    return 0;
}