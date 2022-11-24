#ifndef ANAGRAM_H 
#define ANAGRAM_H

#include <algorithm>
#include <string>
#include <vector>

namespace anagram {
    class anagram {
        std::string m_input;

        public:
            anagram(std::string input);
            std::vector<std::string> matches(std::vector<std::string> words);
    };
}

#endif
