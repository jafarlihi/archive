#include "parse.h"
#include "lex.h"
#include "err.h"

#include <stdlib.h>

#include <strings.h>

int getKeywordType(char *lexeme) {
    if (!strcasecmp("entry", lexeme)) return DIRECTIVE_ENTRY;
    if (!strcasecmp("d32", lexeme)) return DIRECTIVE_D32;
    if (!strcasecmp("ascii", lexeme)) return DIRECTIVE_ASCII;
    if (!strcasecmp("asciz", lexeme)) return DIRECTIVE_ASCIZ;
    if (!strcasecmp("mov", lexeme)) return MNEMONIC_MOV;
    if (!strcasecmp("add", lexeme)) return MNEMONIC_ADD;
    if (!strcasecmp("push", lexeme)) return MNEMONIC_PUSH;
    if (!strcasecmp("pop", lexeme)) return MNEMONIC_POP;
    if (!strcasecmp("int", lexeme)) return MNEMONIC_INT;
    if (!strcasecmp("halt", lexeme)) return MNEMONIC_HALT;
    if (!strcasecmp("call", lexeme)) return MNEMONIC_CALL;
    if (!strcasecmp("ret", lexeme)) return MNEMONIC_RET;
    if (!strcasecmp("jmp", lexeme)) return MNEMONIC_JMP;
    if (!strcasecmp("eax", lexeme)) return REGISTER_EAX;
    if (!strcasecmp("ebx", lexeme)) return REGISTER_EBX;
    if (!strcasecmp("ecx", lexeme)) return REGISTER_ECX;
    if (!strcasecmp("edx", lexeme)) return REGISTER_EDX;
    if (!strcasecmp("esp", lexeme)) return REGISTER_ESP;
    if (!strcasecmp("ebp", lexeme)) return REGISTER_EBP;
    if (!strcasecmp("eip", lexeme)) return REGISTER_EIP;
    if (!strcasecmp("eflags", lexeme)) return REGISTER_EFLAGS;
    return 0;
}

typedef Token **TokenStream;
static TokenStream ts = NULL;
static int ts_length = 0;
static const int ALLOC_STEP_SIZE = 10;

#ifdef DEBUG
void printTokens() {
    for (int i = 0; i < ts_length; i++) {
        printDbg("%s %s", "TT:", getTokenName(ts[i]->type));
        if (ts[i]->sym != NULL) {
            printDbg("%s %s", "SYM->LEXEME:", ts[i]->sym->lexeme);
            printDbg("%s %d", "SYM->LINE:", ts[i]->sym->line);
            printDbg("%s %d", "SYM->COL:", ts[i]->sym->col);
        } else printDbg("%s", "NULL sym pointer.");
    }
}
#endif

// TODO: Extract dynarray as standard DS
void addToken(Token *t) {
    if (ts == NULL)
        ts = malloc(sizeof(Token *) * ALLOC_STEP_SIZE);
    if ((ts_length + 1) % ALLOC_STEP_SIZE == 0)
        ts = realloc(ts, sizeof(Token *) * (ts_length + 1 + ALLOC_STEP_SIZE));
    ts[ts_length] = t;
    ts_length++;
}

static void freeTokenStream() {
    for (int i = 0; i < ts_length; i++) {
        freeToken(ts[i]);
    }
    free(ts);
}

void resetTokenStream() {
    freeTokenStream();
    ts_length = 0;
}

static int error = 0;
inline int errExistsParse() {
    return error;
}

char *parse() {
    for (int i = 0; i < ts_length; i++) {
        printInfo("%s", ts[i]->sym->lexeme);
    }
}
