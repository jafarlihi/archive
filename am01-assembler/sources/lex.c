#include "lex.h"
#include "sym.h"
#include "parse.h"
#include "err.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

char *getTokenName(TT token_type) {
    switch (token_type) {
        case 0: return "TT_EOF"; break;
        case 1: return "TT_DIRECTIVE"; break;
        case 2: return "TT_MNEMONIC"; break;
        case 3: return "TT_REGISTER"; break;
        case 4: return "TT_LABEL_DECL"; break;
        case 5: return "TT_LABEL"; break;
        case 6: return "TT_STRING"; break;
        case 7: return "TT_DEC"; break;
        case 8: return "TT_HEX"; break;
        case 9: return "TT_PLUS"; break;
        case 10: return "TT_MINUS"; break;
        case 11: return "TT_STAR"; break;
        case 12: return "TT_SLASH"; break;
        case 13: return "TT_O_BRACK"; break;
        case 14: return "TT_C_BRACK"; break;
    }
}

static char *buffer;
static char *la = NULL;
static int line = 1;
static int col = 0;

static int error = 0;

inline int errExistsLex() {
    return error;
}

void resetLex() {
    buffer = NULL;
    la = NULL; line = 1; col = 0;
}

void initLex(char *buff) {
    resetLex();
    buffer = buff;
    assert(*(buffer + strlen(buffer)) == '\0');
}

void freeToken(Token *t) {
    free(t->sym->lexeme);
    freeSE(t->sym);
    free(t);
}

static Token *createToken(TT type, SE *sym) {
    Token *t = malloc(sizeof(Token));
    t->type = type;
    t->sym = sym;
    return t;
}

inline static void advance() {
    if (la == NULL) la = buffer;
    else if (*la == '\n') { la++; col = 1; line++; }
    else { la++; col++; }
}

inline static int isEnd() {
    if (la == NULL) return 0;
    if (*la == '\0') return 1;
    else return 0;
}

inline static TT determineTT(char *lexeme) {
    int type = getKeywordType(lexeme);
    if (type == 0) return TT_LABEL;
    if (type < 100) return TT_DIRECTIVE;
    if (type < 200) return TT_MNEMONIC;
    return TT_REGISTER;
}

static char *copyLexeme(char *lexeme_start, int lexeme_length) {
    char *lexeme = malloc(sizeof(lexeme_length + 1));
    strncpy(lexeme, lexeme_start, lexeme_length);
    lexeme[lexeme_length] = '\0';
    return lexeme;
}

SE *prev_labeldecl_SE = NULL;

Token *lex() {
    while (!isEnd()) {
        advance();
        while (isspace(*la)) advance();

        char *start = la;
        int savedLine = line;
        int savedCol = col;

        switch (*la) {
            case ';':
                while (*la != '\0' && *la != '\n') advance();
                break;
            case '+':
                return createToken(TT_PLUS,
                        createSE(copyLexeme(start, 1), savedLine, savedCol));
                break;
            case '-':
                return createToken(TT_MINUS,
                        createSE(copyLexeme(start, 1), savedLine, savedCol));
                break;
            case '*':
                return createToken(TT_STAR,
                        createSE(copyLexeme(start, 1), savedLine, savedCol));
                break;
            case '/':
                return createToken(TT_SLASH,
                        createSE(copyLexeme(start, 1), savedLine, savedCol));
                break;
            case '[':
                return createToken(TT_O_BRACK,
                        createSE(copyLexeme(start, 1), savedLine, savedCol));
                break;
            case ']':
                return createToken(TT_C_BRACK,
                        createSE(copyLexeme(start, 1), savedLine, savedCol));
                break;
            default:
                if (*la == '"') {
                    int length = 2;
                    advance();
                    while (*la != '\0' && *la != '"' && *la != '\n') {
                        advance();
                        length++;
                    }
                    if (*la == '"')
                        return createToken(TT_STRING,
                                createSE(copyLexeme(start, length), savedLine, savedCol));
                    else {
                        char *lexeme = copyLexeme(start, length);
                        printErr("%s: [%d:%d] %s", "Closing quote of the string literal is missing",
                                savedLine, savedCol, lexeme);
                        free(lexeme);
                        error = 1;
                    }
                }
                if (*la == '0' && *(la + 1) == 'x' && isxdigit(*(la+2))) {
                    int length = 3;
                    advance(); advance();
                    while (*la != '\0' && isxdigit(*(la + 1))) {
                        advance();
                        length++;
                    }
                    return createToken(TT_HEX,
                            createSE(copyLexeme(start, length), savedLine, savedCol));
                }
                if (isdigit(*la)) {
                    int length = 1;
                    while (*la != '\0' && isdigit(*(la + 1))) {
                        advance();
                        length++;
                    }
                    return createToken(TT_DEC,
                            createSE(copyLexeme(start, length), savedLine, savedCol));
                }
                if (isalpha(*la)) {
                    int length = 1;
                    while (*la != '\0' && !isspace(*(la + 1))) {
                        advance();
                        length++;
                    }
                    if (*la == ':') {
                        prev_labeldecl_SE = createSE(copyLexeme(start, length - 1), savedLine, savedCol);
                        advance();
                    } else {
                        char *lexeme = copyLexeme(start, length);
                        TT ttype = determineTT(lexeme);
                        Token *token = createToken(ttype, createSE(lexeme, savedLine, savedCol));
                        if (prev_labeldecl_SE != NULL && (ttype == TT_DIRECTIVE || ttype == TT_MNEMONIC)) {
                            insertLabelLink(prev_labeldecl_SE, token);
                            prev_labeldecl_SE = NULL;
                        }
                        return token;
                    }
                }
                if (!isspace(*la) && *la != '\0') {
                    printErr("%s: [%d:%d] %c", "Character didn't match any of the lexer branches",
                            line, col, *la);
                    error = 1;
                }
                break;
        }
    }

    return createToken(TT_EOF, NULL);
}
