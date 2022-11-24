#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <map>
#include <string>

namespace word_count {
    std::map<std::string, int> words(std::string input);
}

#endif
