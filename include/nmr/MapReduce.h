#ifndef MAPREDUCE_TEST_H
#define MAPREDUCE_TEST_H
#include <iostream>
#include <string>
#include "nmr/Map.h"
#include "nmr/Vector.h"
#include "nmr/Queue.h"
#include "nmr/StringUtils.h"

namespace nmr {
    template<typename K1, typename V1, typename K2, typename V2>
    class Mapper {
    public:
        virtual ~Mapper() = default;
        virtual void map(const K1& key, const V1& value, Map<K2, nmr::Vector<V2>>& intermediate) = 0;
    };

    template<typename K2, typename V2, typename V3>
    class Reducer {
        public:
        virtual ~Reducer() = default;
        virtual V3 reduce(const K2& key, const nmr::Vector<V2>& values) = 0;
    };

    class WordCountMapper : public Mapper<int, std::string, std::string, int> {
        public:
        void map(const int&, const string& line, nmr::Map<string, Vector<int>>& intermediate) override {
            std::string cleanLine = nmr::StringUtils::removePunctuation(line);
            nmr::Vector<std::string> words;
            nmr::StringUtils::splitToStringArray(cleanLine, " ", words);
            for (size_t i = 0; i < words.getSize(); ++i)
                intermediate[words[i]].push_back(1);
        }

    };

    class WordCountReducer : public Reducer<std::string, int, int> {
    public:
        int reduce(const std::string&, const nmr::Vector<int>& values) override {
            int sum = 0;
            for (size_t i = 0; i < values.getSize(); ++i) {
                sum += values[i];
            }
            return sum;
        }
    };



}

#endif