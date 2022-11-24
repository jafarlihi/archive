#include "unity.h"
#include "lex.h"

#include <stdlib.h>

void test_dec(void) {
    char buffer[] = "666\0";
    initLex(buffer);
    Token *t = lex();
    TEST_ASSERT_EQUAL_INT(TT_DEC, t->type);
}

void test_hex(void) {
    char buffer[] = "0x 0x6AFA22\0";
    initLex(buffer);
    Token *t = lex();
    TEST_ASSERT_EQUAL_INT(0, atoi(t->sym->lexeme));
    lex();
    t = lex();
    TEST_ASSERT_EQUAL_STRING("0x6AFA22", t->sym->lexeme);
    TEST_ASSERT_EQUAL_INT(TT_HEX, t->type);
}

void test_singles(void) {
    char buffer[] = "+-*/[];";
    initLex(buffer);
    Token *t = lex();
    TEST_ASSERT_EQUAL_STRING("+", t->sym->lexeme);
    TEST_ASSERT_EQUAL_INT(TT_PLUS, t->type);
    lex(); lex(); lex(); lex();
    t = lex();
    TEST_ASSERT_EQUAL_STRING("]", t->sym->lexeme);
    TEST_ASSERT_EQUAL_INT(TT_C_BRACK, t->type);
}

void test_comments(void) {
    char buffer[] = ";5nothing0x20A";
    initLex(buffer);
    Token *t = lex();
    TEST_ASSERT_EQUAL_INT(TT_EOF, t->type);
    char buffer2[] = "0x6AF ; this is a comment 50\n230\n*;another comment";
    initLex(buffer2);
    t = lex();
    TEST_ASSERT_EQUAL_INT(TT_HEX, t->type);
    t = lex();
    TEST_ASSERT_EQUAL_INT(TT_DEC, t->type);
    t = lex();
    TEST_ASSERT_EQUAL_INT(TT_STAR, t->type);
}

void test_strings(void) {
    char buffer[] = "entry start\nnumber: d32 663\nlalala: d32 0x6F6A\nstring: ascii \"test\"\nstr: asciz \"duktrukduk dukdruek\"\nstart: ; comments\nmov 3 EAX\nadd number EAX\npush EAX ; 666 comment\nint 0x20\n7\n0x";
    initLex(buffer);
    Token *t = lex();
    TEST_ASSERT_EQUAL_INT(TT_DIRECTIVE, t->type);
    lex(); lex(); lex(); lex(); lex(); lex(); lex(); lex();
    t = lex();
    TEST_ASSERT_EQUAL_INT(TT_DIRECTIVE, t->type);
    t = lex();
    TEST_ASSERT_EQUAL_INT(TT_STRING, t->type);
}
