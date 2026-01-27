#include "nmr/StringUtils.h"
#include "nmr/Vector.h"
#include <iostream>
using namespace std;
namespace nmr {

// Define static punctuation constant (implementation)
const string StringUtils::punctuations = ",;?!.\"'()[]{}_-";

/**
 * @brief Remove punctuation implementation
 * 
 * Nested loop logic:
 * 1. Iterate each character in input string
 * 2. Check if character is in punctuation list
 * 3. Keep only non-punctuation characters
 */
string StringUtils::removePunctuation(string str) {
    string result;
    
    // Iterate through each character in input string
    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];
        bool isPunct = false;

        // Check if character is punctuation
        for (size_t j = 0; j < punctuations.length(); ++j) {
            if (c == punctuations[j]) {
                isPunct = true;
                break; // Exit inner loop early if match found
            }
        }

        // Keep non-punctuation characters
        if (!isPunct) {
            result += c;
        }
    }

    return result;
}

    nmr::Vector<size_t> StringUtils::getDelimiterLocation(const std::string& s, const std::string& delimiter) {
    nmr::Vector<size_t> loc;
    const size_t delimiter_len = delimiter.length();
    const size_t s_len = s.length();

    if (delimiter_len == 0 || s_len == 0)
        return loc;

    for (size_t i = 0; i < s_len; i++) {
        char str = s[i];
        bool isPunct = false;
        for (size_t j = 0; j < delimiter_len; ++j) {
            if (str == delimiter[j]){
                isPunct = true;
                break;
            }
        }
        if (isPunct)
            loc.push_back(i);
    }
    return loc;
}

size_t StringUtils::splitToStringArray(const string& str, const string& delimiter, nmr::Vector<string> &out_words){
    string substr;
    size_t start = 0;
    nmr::Vector<size_t> loc = getDelimiterLocation(str, delimiter);
    size_t count = loc.getSize() + 1;
    for (size_t idx : loc) {
        while (start < idx) {
            substr += str[start];
            start++;
            }
        start = idx + 1;
        out_words.push_back(substr);
        }
        return count;
}

} // namespace nmr