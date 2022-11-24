#include "anagram.h"
#include <string.h>
#include <stdbool.h>

bool is_anagram(char * input1, char * input2) {

}

struct Vector anagrams_for(char * word, struct Vector tests) {
    for (unsigned int i = 0; i < tests.size; i++) {
        if (strlen(tests.vec[i]) == strlen(word)) {
            if (is_anagram(word, tests.vec[i])) {
                // Add to result
            }
        }
    }
}
