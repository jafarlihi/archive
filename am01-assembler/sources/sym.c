#include "sym.h"
#include "lex.h"

#include <stdlib.h>
#include <string.h>

SE *createSE(char *lexeme, int line, int col) {
    SE *se = malloc(sizeof(SE));
    se->line = line;
    se->col = col;
    se->lexeme = lexeme;
    se->label_link = NULL;
    return se;
}

void insertLabelLink(SE *sym, Token *t) {
    sym->label_link = t;
    // insert sym ptr to labelDecl dynarray
}

Token *getLabelLink(char *lexeme) {
    // compare all labelDecl dynarray elems to lexeme+':' and return matching elem's label_link
}

void freeSE(SE *sym) {
    free(sym);
}
