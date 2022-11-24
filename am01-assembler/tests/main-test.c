#include "unity.h"

extern void test_dec(void);
extern void test_hex(void);
extern void test_singles(void);
extern void test_comments(void);
extern void test_strings(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_dec);
    RUN_TEST(test_hex);
    RUN_TEST(test_singles);
    RUN_TEST(test_comments);
    RUN_TEST(test_strings);
    return UNITY_END();
}
