#include "lex.h"
#include "parse.h"
#include "err.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printErr("%s", "usage: assembler [file]");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printErr("%s: %s", "fopen", strerror(errno));
        return 2;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    fread(buffer, file_size, 1, file);
    fclose(file);
    buffer[file_size] = '\0';

    initLex(buffer);

    Token *t;
    while ((t = lex())->type != TT_EOF) addToken(t);
    free(buffer);

#ifdef DEBUG
    printTokens();
#endif

    char *gen;
    if (!errExistsLex()) gen = parse();
    else printErr("%s", "Lexer errors are present. Not continuing.");

    if (!errExistsParse()) {} // TODO: Dump gen to file

    resetTokenStream(); // This should free TokenStream which should free Tokens which should free SymEntries

    return 0;
}
