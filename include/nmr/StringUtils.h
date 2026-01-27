#ifndef NMR_STRING_UTILS_H
#define NMR_STRING_UTILS_H
#include "nmr/Vector.h"
#include <iostream>
#include <string>
#include <cstddef>
using namespace std;
namespace nmr {

/**
 * @brief Utility class for string manipulation (static methods only)
 * 
 * Provides static functions for common string operations:
 * - Punctuation removal
 * - String splitting (extendable)
 * - Case conversion (extendable)
 * 
 * All methods are static (no instantiation required)
 */
class StringUtils {
private:
    /**
     * @brief Static constant for punctuation characters to remove
     * Includes common punctuation: , ; ? ! . " ' ( ) [ ] { } - _
     */
    static const string punctuations;

public:
    /**
     * @brief Remove all punctuation characters from a string
     * 
     * Iterates through each character in the input string and keeps only
     * non-punctuation characters (letters, numbers, spaces, etc.)
     * 
     * @param str Input string to process
     * @return Cleaned string with no punctuation
     */
    static string removePunctuation(string str);
    static Vector<size_t> getDelimiterLocation(const string& str, const string& delimiter);
    static size_t splitToStringArray(const string& str, const string& delimiter, string*&out_words);
};

} // namespace nmr

#endif // NMR_STRING_UTILS_H