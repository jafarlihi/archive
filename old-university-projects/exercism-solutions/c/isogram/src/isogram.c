#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "isogram.h"

bool isIsogram(const char *input) {
    int charHit[26] = {0};

    for (unsigned int i = 0; i < strlen(input); i++) {
        if isalpha(input[i]) {
            if (charHit[tolower(input[i]) - 'a'] > 0) {
                return false;
            }
            charHit[tolower(input[i]) - 'a']++;
        }
    }

    return true;
}
