//
// Created by Jeff Whynot on 2026/1/28.
//

#include "nmr/MapReduce.h"

int main() {
    nmr::WordCountMapper wordCountMapper;
    nmr::WordCountReducer wordCountReducer;
    nmr::Map<std::string, nmr::Vector<int>> map;
    std::string str = "hello,world,cpp.hello,world,python.";
    int line = 0;
    wordCountMapper.map(line ,str, map);
    nmr::Vector<int> vec;
    std::string str2 = "hello,world,cpp.hello,world,python.";
    wordCountReducer.reduce(str2, vec);
    return 0;
}