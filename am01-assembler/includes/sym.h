#ifndef SYM_H
#define SYM_H

#include "lex.h"

typedef struct SE {
    char *lexeme;
    int line;
    int col;
    Token *label_link;
} SE;

SE *createSE(char *lexeme, int line, int col);
void insertLabelLink(SE *sym, Token *t);
Token *getLabelLink(char *lexeme);
void freeSE(SE *sym);

#endif
