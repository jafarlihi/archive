#include "anagram.h"

namespace anagram {

anagram::anagram(std::string input) {
    m_input = input;
    std::transform(m_input.begin(), m_input.end(), m_input.begin(), ::tolower);
}

std::vector<std::string> anagram::matches(std::vector<std::string> words) {
    std::vector<std::string> result;
    
    int inputLength = m_input.length();
    std::vector<std::string> sameLengthWords;
    std::string temp_word;

    for (std::string &word : words) { 
        if (word.length() == inputLength) {
            temp_word = word;
            std::transform(temp_word.begin(), temp_word.end(), temp_word.begin(), ::tolower);

            if (m_input != temp_word) {
                sameLengthWords.push_back(word);
            }
        }
    }

    bool flag = true;
    int index;

    for (std::string &word : sameLengthWords) {
        flag = true;
        std::string temp_input = m_input;

        for (int i = 0; i < word.length(); i++) {
            index = temp_input.find(std::tolower(word[i]), 0);
            
            if (index != -1) {
               temp_input.erase(temp_input.begin() + index);
            } else {
                flag = false;
                break;
            }
        }
        
        if (flag == true) {
            result.push_back(word);
        }
    }

    return result;
}
    
}
