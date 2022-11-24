#ifndef PARSE_H
#define PARSE_H

#include "lex.h"

typedef enum DIRECTIVE {
    DIRECTIVE_ENTRY = 1,
    DIRECTIVE_D32,
    DIRECTIVE_ASCII,
    DIRECTIVE_ASCIZ,
} DIRECTIVE;

typedef enum MNEMONIC {
    MNEMONIC_MOV = 100,
    MNEMONIC_ADD,
    MNEMONIC_PUSH,
    MNEMONIC_POP,
    MNEMONIC_INT,
    MNEMONIC_HALT,
    MNEMONIC_CALL,
    MNEMONIC_RET,
    MNEMONIC_JMP,
} MNEMONIC;

typedef enum REGISTER {
    REGISTER_EAX = 200,
    REGISTER_EBX,
    REGISTER_ECX,
    REGISTER_EDX,
    REGISTER_ESP,
    REGISTER_EBP,
    REGISTER_EIP,
    REGISTER_EFLAGS,
} REGISTER;

int getKeywordType(char *lexeme);

void addToken(Token *t);
void resetTokenStream();
int errExistsParse();
char *parse();

#ifdef DEBUG
void printTokens();
#endif

#endif
