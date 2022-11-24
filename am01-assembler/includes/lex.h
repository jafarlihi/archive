#ifndef LEX_H
#define LEX_H

typedef struct Token Token;
typedef struct SE SE;

#include "sym.h"

typedef enum TT {
    TT_EOF = 0,
    TT_DIRECTIVE,
    TT_MNEMONIC,
    TT_REGISTER,
    TT_LABEL_DECL,
    TT_LABEL,
    TT_STRING,
    TT_DEC,
    TT_HEX,
    TT_PLUS,
    TT_MINUS,
    TT_STAR,
    TT_SLASH,
    TT_O_BRACK,
    TT_C_BRACK,
} TT;

typedef struct Token {
    TT type;
    SE *sym;
} Token;

void initLex(char *buff);
Token *lex();
int errExistsLex();
void resetLex();
void freeToken(Token *t);
char *getTokenName(TT token_type);

#endif
