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

    Vector<size_t> StringUtils::getDelimiterLocation(const std::string& s, const std::string& delimiter) {
    Vector<size_t> loc; // 指定模板类型 size_t
    const size_t delimiter_len = delimiter.length();
    const size_t s_len = s.length();

    // 边缘场景1：分隔符为空 → 返回空向量
    if (delimiter_len == 0) {
        std::cerr << "[StringUtils Warning] Delimiter is empty - return empty location list" << std::endl;
        return loc;
    }

    // 边缘场景2：字符串为空 → 返回空向量
    if (s_len == 0) {
        return loc;
    }

    // 遍历字符串（i 最大为 s_len - delimiter_len，避免越界）
    for (size_t i = 0; i <= s_len - delimiter_len; ++i) {
        bool is_match = true;

        // 验证完整分隔符匹配
        for (size_t j = 0; j < delimiter_len; ++j) {
            if (s[i + j] != delimiter[j]) {
                is_match = false;
                break;
            }
        }

        // 匹配成功：记录位置 + 跳过已匹配的字符（避免重复）
        if (is_match) {
            loc.push_back(i);
            i += delimiter_len - 1; // 比如分隔符长度3，i 直接+2，下次从i+3开始
        }
    }

    return loc;
}

size_t StringUtils::splitToStringArray(const string& str, 
                                       const string& delimiter,
                                       string*& out_words){
        string clean_str = removePunctuation(str);
        string s = clean_str;
        size_t count = 0;
        size_t delimiter_len = delimiter.length();
        size_t start = 0;
        for (size_t i = 0; i <= s.length(); i++) {
            bool is_delimiter = false;
            if (i + delimiter_len <= s.length()) {
                is_delimiter = true;
                for (size_t j = 0; j < delimiter_len; j++) {
                    if (s[i + j] != delimiter[j]) {
                        is_delimiter = false;
                        break;
                    }
                }
            }
            if (is_delimiter || i == s.length()) {
                size_t word_len = i - start;
                if (word_len > 0) {
                    count++;
                }
                start = i + delimiter_len;
                if (is_delimiter) {
                    i += delimiter_len - 1;
                }
            }
        }
        cout << "Cleaned string: " << s << " " << "count: " << count  << " " << 
        "delimiter_len: "<< delimiter_len << endl;

        out_words = new string[count];
        return count;
        
}

} // namespace nmr