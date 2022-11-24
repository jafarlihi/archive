#include "table.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void printTest(int undeffed) {
    printf("test: %s\n", hashtab[hash("test")]->defn);
    if (!undeffed)
        printf("anotherTestValue: %s\n", hashtab[hash("anotherTestValue")]->defn);
    printf("oneMore: %s\n", hashtab[hash("oneMore")]->defn);
}

int main(int argc, char** argv) {
    install("test", "23");
    install("anotherTestValue", "23");
    install("oneMore", "23");
    printTest(0);

    undef("anotherTestValue");
    printTest(1);

    return 0;
}

unsigned hash(char* s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

struct nlist* lookup(char* s) {
    struct nlist* np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;

    return NULL;
}

struct nlist* install(char* name, char* defn) {
    struct nlist* np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist*)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else 
        free((void*)np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}

int undef(char* name) {
    struct nlist* np;
    np = lookup(name);

    if (np == NULL)
        return 1;

    np = hashtab[hash(name)];
    for (struct nlist* temp = np; np != NULL; temp = np, np = np->next) {
        if (strcmp(name, np->name) == 0) {
            if (np == temp)
                hashtab[hash(name)] = np->next;
            else
                temp->next = np->next;

            // free dem mallocs
            free(np->name);
            free(np->defn);
            free(np);

            return 0;
        }
    }

    return 1; // odd
}
