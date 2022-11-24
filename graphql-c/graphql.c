#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
  int line;
  int column;
} Location;

typedef struct {
  char *body;
  char *name;
  Location *locationOffset;
} Source;

typedef enum {
  SOF,
  EOFILE,
  BANG,
  QUESTION_MARK,
  DOLLAR,
  AMP,
  PAREN_L,
  PAREN_R,
  SPREAD,
  COLON,
  EQUALS,
  AT,
  BRACKET_L,
  BRACKET_R,
  BRACE_L,
  PIPE,
  BRACE_R,
  NAME,
  INT,
  FLOAT,
  STRING,
  BLOCK_STRING,
  COMMENT,
} TokenKind;

typedef struct {
  TokenKind kind;
  int start;
  int end;
  int line;
  int column;
  char *value;
  struct Token *prev;
  struct Token *next;
} Token;

typedef struct {
  Source *source;
  Token *lastToken;
  Token *token;
  int line;
  int lineStart;
} Lexer;

char *slice(char *str, int start, int end) {
    int i;
    int size = (end - start) + 2;
    char *output = (char *)malloc(size * sizeof(char));

    for (i = 0; start <= end; start++, i++)
        output[i] = str[start];
    output[size] = '\0';

    return output;
}

Token *createToken(Lexer *lexer, TokenKind kind, int start, int end, char *value) {
  int line = lexer->line;
  int column = 1 + start - lexer->lineStart;
  Token *token = (Token *)malloc(sizeof(Token));
  token->kind = kind;
  token->start = start;
  token->end = end;
  token->line = line;
  token->column = column;
  token->value = value;
  return token;
}

Token *readComment(Lexer *lexer, int start) {
  char *body = lexer->source->body;
  int bodyLength = strlen(body);
  int position = start + 1;

  while (position < bodyLength) {
    char code = body[position];

    if (code == '\n' || code == '\r')
      break;

    // TODO-UNICODE:

    break;
  }

  return createToken(lexer, COMMENT, start, position, slice(body, start + 1, position));
}

Token *readBlockString(Lexer *lexer, int start) {

}

Token *readString(Lexer *lexer, int start) {

}

Token *readNumber(Lexer *lexer, int start, char firstCode) {

}

Token *readName(Lexer *lexer, int start) {

}

bool isNameStart(char code) {
  return isalnum(code) || code == '_';
}

Token *readNextToken(Lexer *lexer, int start) {
  char *body = lexer->source->body;
  int bodyLength = strlen(body);
  int position = start;

  while (position < bodyLength) {
    char code = body[position];

    switch (code) {
      // TODO-UNICODE: BOM
      case '\t':
      case ' ':
      case ',':
        ++position;
        continue;
      case '\n':
        ++position;
        ++lexer->line;
        lexer->lineStart = position;
        continue;
      case '\r':
        if (body[position + 1] == '\n') {
          position += 2;
        } else {
          ++position;
        }
        ++lexer->line;
        lexer->lineStart = position;
        continue;
      case '#':
        return readComment(lexer, position);
      case '!':
        return createToken(lexer, BANG, position, position + 1, NULL);
      case '$':
        return createToken(lexer, DOLLAR, position, position + 1, NULL);
      case '&':
        return createToken(lexer, AMP, position, position + 1, NULL);
      case '(':
        return createToken(lexer, PAREN_L, position, position + 1, NULL);
      case ')':
        return createToken(lexer, PAREN_R, position, position + 1, NULL);
      case '.':
        if (body[position + 1] == '.' && body[position + 2] == '.')
          return createToken(lexer, SPREAD, position, position + 3, NULL);
        break;
      case ':':
        return createToken(lexer, COLON, position, position + 1, NULL);
      case '=':
        return createToken(lexer, EQUALS, position, position + 1, NULL);
      case '@':
        return createToken(lexer, AT, position, position + 1, NULL);
      case '[':
        return createToken(lexer, BRACKET_L, position, position + 1, NULL);
      case ']':
        return createToken(lexer, BRACKET_R, position, position + 1, NULL);
      case '{':
        return createToken(lexer, BRACE_L, position, position + 1, NULL);
      case '|':
        return createToken(lexer, PIPE, position, position + 1, NULL);
      case '}':
        return createToken(lexer, BRACE_R, position, position + 1, NULL);
      case '?':
        return createToken(lexer, QUESTION_MARK, position, position + 1, NULL);
      case '"':
        if (body[position + 1] == '"' && body[position + 2] == '"')
          return readBlockString(lexer, position);
        return readString(lexer, position);
    }

    if (isdigit(code) || code == '-')
      return readNumber(lexer, position, code);

    if (isNameStart(code))
      return readName(lexer, position);

    // TODO: Unexpected character
  }

  return createToken(lexer, EOFILE, bodyLength, bodyLength, NULL);
}

Token *lookahead(Lexer *lexer) {
  Token *token = lexer->token;
  if (token->kind != EOFILE) {
    do {
      if (token->next) {
        token = (Token *)token->next;
      } else {
        Token *nextToken = readNextToken(lexer, token->end);

        token->next = (struct Token *)nextToken;
        nextToken->prev = (struct Token *)token;
        token = nextToken;
      }
    } while (token->kind == COMMENT);
  }
  return token;
}

Token *advance(Lexer *lexer) {
  lexer->lastToken = lexer->token;
  lexer->token = lookahead(lexer);
  return lexer->token;
}

