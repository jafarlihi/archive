#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char* int2bin(int i) {
    size_t bits = sizeof(int) * CHAR_BIT;

    char* str = malloc(bits + 1);
    if(!str) return NULL;
    str[bits] = 0;

    unsigned u = *(unsigned *)&i;
    for(; bits--; u >>= 1)
        str[bits] = u & 1 ? '1' : '0';

    return str;
}

/* setbits:  replace n bits from position p with rightmost n bits of y */
unsigned setbits(unsigned x, int p, int n, unsigned y) {
    int mask = INT_MAX >> ((sizeof(int) * 8) - n) - 1;
    y = (y & mask) << (p + 1 - n);

    mask = ~(~(~0 << n) << (p + 1 - n));
    x = (x & mask) | y;

    return x;
}

int main(int argc, char** argv) {
    int x;
    scanf("%d", &x);
    printf("%s\n", int2bin(x));
 
    int p, n;
    scanf("%d", &p);
    scanf("%d", &n);

    int y;
    scanf("%d", &y);
    printf("%s\n", int2bin(y));

    printf("%s\n", int2bin(setbits(x, p, n, y)));

    return 0;
}
