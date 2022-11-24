#include "hamming.h"

namespace hamming {

int compute(std::string input1, std::string input2) {
    if (input1 == input2) { return 0; }

    if (input1.length() != input2.length()) { 
        throw std::domain_error("Lengths of inputs are not equal."); 
    }

    int count = 0;

    for (int i = 0; i < input1.length(); i++) {
        if (input1[i] != input2[i]) {
            count++;
        }
    }

    return count;
}

}
