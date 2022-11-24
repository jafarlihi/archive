#include <stdio.h>
#include <string.h>

int strindex(char source[], char searchfor[]);

char pattern[] = "ould";
char line[] = "Ah Love! could you and I with Fate conspire\nTo grasp this sorry Scheme of Things entire,\nWould not we shatter it to bits -- and then\nRe-mould it nearer to the Heart's Desire!";

int main(int argc, char** argv) {
    int found = strindex(line, pattern);
    printf("%d", found);
    return found;
}

/* strindex:  returns index of rightmost occurrence of t in s */
int strindex(char s[], char t[]) {
    int i, j, k;
    int lastIndex = -1;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            lastIndex = i;
    }

    return lastIndex;
}
