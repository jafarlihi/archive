#include "etl.h"

namespace etl {
    std::map<char, int> transform(std::map<int, std::vector<char>> input) {
        std::map<char, int> result;

        for (int i = 0; i <= 10; i++) {
            for (char value : input[i]) {
                char lowerValue = tolower(value);
                result[lowerValue] = i;
            }
        }

        return result;
    }
}
