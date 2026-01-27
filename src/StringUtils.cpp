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

    size_t StringUtils::getDelimiter2Location(const std::string& s,
        const std::string& delimiter,
        nmr::Vector<size_t> &locations,
        nmr::Vector<char> &delimiters) {

        const size_t delimiter_len = delimiter.length();
        const size_t s_len = s.length();

        if (delimiter_len == 0 || s_len == 0)
            return 0;

        for (size_t i = 0; i < s_len; i++) {
            char str = s[i];
            bool isPunct = false;
            for (size_t j = 0; j < delimiter_len; ++j) {
                if (str == delimiter[j]){
                    isPunct = true;
                    break;
                }
            }
            if (isPunct){
                locations.push_back(i);
                delimiters.push_back(s[i]);
            }
        }
        return locations.getSize();
    }

    nmr::Vector<size_t> StringUtils::getDelimiterLocation(const string& s,
        const std::string& delimiter) {
        const size_t delimiterLen = delimiter.length();
        const size_t s_len = s.length();
        nmr::Vector<size_t> locations;
        locations.clear();

        if (delimiterLen == 0)
            return locations;
        for (size_t i = 0; i < s_len; i++) {
            char str = s[i];
            bool isPunct = false;
            for (size_t j = 0; j < delimiterLen; ++j) {
                if (str == delimiter[j]) {
                    isPunct = true;
                    break;
                }
            }
            if (isPunct)
                locations.push_back(i);
        }
        return locations;
    }

    size_t StringUtils::splitToStringArray(const string& str,
        const string& delimiter,
        nmr::Vector<string> &out_words) {

        out_words.clear();
        string substr;
        substr.clear();
        size_t start = 0;
        nmr::Vector<size_t> locations;
        nmr::Vector<char> delimiters;
        nmr::StringUtils::getDelimiter2Location(str, delimiter, locations, delimiters);
        for (const size_t idx : locations) {
            for (size_t i = start; i < idx; ++i)
                substr += str[i];
            if (!substr.empty())
                out_words.push_back(substr);
            start = idx + 1;
            substr.clear();
        }

        return out_words.getSize();
    }
    size_t StringUtils::splitToStringArray_(const string& str,
        const string& delimiter,
        nmr::Vector<string> &out_words) {
        out_words.clear();
        size_t start = 0;
        string substr;
        nmr::Vector<size_t> locs = nmr::StringUtils::getDelimiterLocation(str, delimiter);
        for (const size_t idx : locs) {
            for (size_t i = start; i < idx; ++i)
                substr += str[i];
            if (!substr.empty())
                out_words.push_back(substr);
            start = idx + 1;
            substr.clear();
        }
        return out_words.getSize();
    }
} // namespace nmr