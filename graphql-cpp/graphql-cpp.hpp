// graphql-js: 8a7c6698cd2acfac3c498fdae280c2b324cc99e3
#pragma once

#include <memory>
#include <string>
#include <cwctype>
#include <vector>
#include <limits.h>
#include <iostream> // TODO DELETE
#include <numeric>
#include <functional>
#include <set>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

#undef EOF
#undef NULL

#define DEBUG 1

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept {
  return static_cast<typename std::underlying_type<E>::type>(e);
}


namespace graphql {
  enum class TokenKind {
    SOF,
    EOF,
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
  };

  class SourceLocation {
    public:
      int line;
      int column;

      SourceLocation() {
        this->line = 1;
        this->column = 1;
      }

      SourceLocation(int line, int column) {
        this->line = line;
        this->column = column;
      }
  };

  std::vector<std::wstring> splitString(const std::wstring &str, const std::wstring &delimiter) {
    std::vector<std::wstring> strings;
    std::wstring::size_type pos = 0;
    std::wstring::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::wstring::npos) {
      strings.push_back(str.substr(prev, pos - prev));
      prev = pos + 1;
    }
    strings.push_back(str.substr(prev));
    return strings;
  }

  class Source {
    public:
      std::wstring body;
      std::string name;
      SourceLocation locationOffset;

      Source(std::wstring body, std::string name = "GraphQL request", SourceLocation locationOffset = SourceLocation(1, 1)) {
        this->body = body;
        this->name = name;
        this->locationOffset = locationOffset;
      }

      SourceLocation get_location(int position) {
        std::vector<std::wstring> lines = splitString(this->body.substr(0, position), L"\n");
        int line, column;
        if (lines.size() > 0) {
          line = lines.size();
          column = lines.back().length() + 1;
        } else {
          line = 1;
          column = 1;
        }
        return SourceLocation(line, column);
      }
  };

  class Token {
    public:
      TokenKind kind;
      int start;
      int end;
      int line;
      int column;
      std::wstring value;
      Token *prev;
      Token *next;

      Token(TokenKind kind, int start, int end, int line, int column, std::wstring value = L"") {
        this->kind = kind;
        this->start = start;
        this->end = end;
        this->line = line;
        this->column = column;
        this->value = value;
        this->next = 0x0;
        this->prev = 0x0;
      }
  };

  class Location {
    public:
      int start;
      int end;
      Token *startToken;
      Token *endToken;
      Source *source;

      Location(Token *startToken, Token *endToken, Source *source) {
        this->start = startToken->start;
        this->end = endToken->end;
        this->startToken = startToken;
        this->endToken = endToken;
        this->source = source;
      }
  };

  class Lexer;
  Token *readNextToken(Lexer *lexer, int start);

  class Lexer {
    public:
      Source *source;
      Token *lastToken;
      Token *token;
      int line;
      int lineStart;

      Lexer(Source *source) {
        Token *startOfFileToken = new Token(TokenKind::SOF, 0, 0, 0, 0);

        this->source = source;
        this->lastToken = startOfFileToken;
        this->token = startOfFileToken;
        this->line = 1;
        this->lineStart = 0;
      }

      Token *advance() {
        this->lastToken = this->token;
        Token *token = this->token = this->lookahead();
        return token;
      }

      Token *lookahead() {
        Token *token = this->token;
        if (token->kind != TokenKind::EOF) {
          do {
            if (token->next)
              token = token->next;
            else {
              Token *nextToken = readNextToken(this, token->end);
              token->next = nextToken;
              nextToken->prev = token;
              token = nextToken;
            }
          } while (token->kind == TokenKind::COMMENT);
        }
        return token;
      }
  };

  Token *createToken(Lexer *lexer, TokenKind kind, int start, int end, std::wstring value = L"") {
    int line = lexer->line;
    int column = 1 + start - lexer->lineStart;
    Token *token = new Token(kind, start, end, line, column, value);
    return token;
  }

  bool isUnicodeScalarValue(wchar_t code) {
    return (
        (code >= 0x00000000 && code <= 0x0000d7ff) || (code >= 0x0000e000 && code <= 0x0010ffff)
        );
  }

  bool isLeadingSurrogate(wchar_t code) {
    return code >= 0x0000d800 && code <= 0x0000dbff;
  }

  bool isTrailingSurrogate(wchar_t code) {
    return code >= 0x0000dc00 && code <= 0x0000dfff;
  }

  bool isSupplementaryCodePoint(std::wstring body, int location) {
    return (
        isLeadingSurrogate(body[location]) &&
        isTrailingSurrogate(body[location + 1])
        );
  }

  std::string printCodePointAt(Lexer *lexer, int location) {
    // TODO
    return "?";
  }

  class GraphQLError : public std::exception {
    public:
      std::string message;
      std::vector<SourceLocation> *locations;
      Source *source;
      std::vector<int> *positions;
      std::exception *originalError;

      GraphQLError(std::string message, Source *source = nullptr, std::vector<int> *positions = nullptr) {
        this->message = message;
        this->source = source;
        this->positions = positions;
        if (positions != nullptr && source != nullptr) {
          std::vector<SourceLocation> *locations = new std::vector<SourceLocation>();
          for (auto &position : *positions) {
            SourceLocation location = source->get_location(position);
            locations->push_back(location);
          }
          this->locations = locations;
        }
      }
  };
  std::vector<int> *positionToPositionList(int position) {
    std::vector<int> *result = new std::vector<int>();
    result->push_back(position);
    return result;
  }

  std::vector<std::wstring> dedentBlockStringLines(
      std::vector<std::wstring> lines
      ) {
    return lines;
    /*
       int commonIndent = INT_MAX;
       int firstNonEmptyLine = -1;
       int lastNonEmptyLine = -1;

       for (int i = 0; i < lines.size(); ++i) {
       std::wstring line = lines[i];
       const indent = leadingWhitespace(line);

       if (indent == line.size()) {
       continue; // skip empty lines
       }

       firstNonEmptyLine = firstNonEmptyLine == -1 ? i : firstNonEmptyLine;
       lastNonEmptyLine = i;

       if (i != 0 && indent < commonIndent) {
       commonIndent = indent;
       }
       }

       return (
       lines
    // Remove common indentation from all lines but first.
    .map((line, i) => (i === 0 ? line : line.slice(commonIndent)))
    // Remove leading and trailing blank lines.
    .slice(firstNonEmptyLine ?? 0, lastNonEmptyLine + 1)
    );
    */
  }

  class GraphQLSyntaxError : public GraphQLError {
    public:
      std::string description;
      GraphQLSyntaxError(Source *source, int position, std::string description) : GraphQLError(fmt::format("Syntax Error: {}", description), source, positionToPositionList(position)), description{description} { }
  };

  Token *readBlockString(Lexer *lexer, int start) {
    std::wstring body = lexer->source->body;
    size_t bodyLength = body.size();
    int lineStart = lexer->lineStart;

    int position = start + 3;
    int chunkStart = position;
    std::wstring currentLine = L"";

    std::vector<std::wstring> blockLines = std::vector<std::wstring>();
    while (position < bodyLength) {
      wchar_t code = body[position];

      if (
          code == 0x00000022 &&
          body[position + 1] == 0x00000022 &&
          body[position + 2] == 0x0022
         ) {
        currentLine += body.substr(chunkStart, position - chunkStart);
        blockLines.push_back(currentLine);


        std::vector<std::wstring> elems = dedentBlockStringLines(blockLines);
        std::wstring acc = std::accumulate(
            std::next(elems.begin()), 
            elems.end(), 
            elems[0], 
            [](std::wstring a, std::wstring b) {
            return a + L"\n" + b;
            }
            );

        Token *token = createToken(
            lexer,
            TokenKind::BLOCK_STRING,
            start,
            position + 3,
            acc
            );

        lexer->line += blockLines.size() - 1;
        lexer->lineStart = lineStart;
        return token;
      }

      if (
          code == 0x0000005c &&
          body[position + 1] == 0x00000022 &&
          body[position + 2] == 0x00000022 &&
          body[position + 3] == 0x00000022
         ) {
        currentLine += body.substr(chunkStart, position - chunkStart);
        chunkStart = position + 1;
        position += 4;
        continue;
      }

      if (code == 0x0000000a || code == 0x0000000d) {
        currentLine += body.substr(chunkStart, position - chunkStart);
        blockLines.push_back(currentLine);

        if (code == 0x0000000d && body[position + 1] == 0x0000000a) {
          position += 2;
        } else {
          ++position;
        }

        currentLine = L"";
        chunkStart = position;
        lineStart = position;
        continue;
      }

      // SourceCharacter
      if (isUnicodeScalarValue(code)) {
        ++position;
      } else if (isSupplementaryCodePoint(body, position)) {
        position += 2;
      } else {
        throw GraphQLSyntaxError(lexer->source, position, "Invalid character within String: " + printCodePointAt(lexer, position) + ".");
      }
    }

    throw GraphQLSyntaxError(lexer->source, position, "Unterminated string.");
  }

  Token *readComment(Lexer *lexer, int start) {
    std::wstring body = lexer->source->body;
    size_t bodyLength = body.size();
    int position = start + 1;

    while (position < bodyLength) {
      wchar_t code = body[position];

      if (code == 0x0000000a || code == 0x0000000d) {
        break;
      }

      if (isUnicodeScalarValue(code)) {
        ++position;
      } else if (isSupplementaryCodePoint(body, position)) {
        position += 2;
      } else {
        break;
      }
    }

    return createToken(
        lexer,
        TokenKind::COMMENT,
        start,
        position,
        body.substr(start + 1, position - start)
        );
  }

  class EscapeSequence {
    public:
      std::wstring value;
      size_t size;
  };


  int readHexDigit(wchar_t code) {
    return code >= 0x00000030 && code <= 0x00000039 // 0-9
      ? code - 0x00000030
      : code >= 0x00000041 && code <= 0x00000046 // A-F
      ? code - 0x00000037
      : code >= 0x00000061 && code <= 0x00000066 // a-f
      ? code - 0x00000057
      : -1;
  }


  EscapeSequence readEscapedUnicodeVariableWidth(Lexer *lexer, int position) {
    std::wstring body = lexer->source->body;
    int point = 0;
    size_t size = 3;
    while (size < 12) {
      wchar_t code = body[position + size++];
      if (code == 0x0000007d) {
        if (size < 5 || !isUnicodeScalarValue(point)) {
          break;
        }
        return EscapeSequence{ .value = std::to_wstring(point), .size = size };
      }
      point = (point << 4) | readHexDigit(code);
      if (point < 0) {
        break;
      }
    }

    std::wstring invalid_seq = body.substr(
        position,
        size
        );

    std::string s(invalid_seq.begin(), invalid_seq.end());

    throw GraphQLSyntaxError(
        lexer->source,
        position,
        "Invalid Unicode escape sequence: " + s + "."
        );
  }

  int read16BitHexCode(std::wstring body, int position) {
    return (
        (readHexDigit(body[position]) << 12) |
        (readHexDigit(body[position + 1]) << 8) |
        (readHexDigit(body[position + 2]) << 4) |
        readHexDigit(body[position + 3])
        );
  }

  EscapeSequence readEscapedUnicodeFixedWidth(
      Lexer *lexer,
      int position
      ) {
    std::wstring body = lexer->source->body;
    int code = read16BitHexCode(body, position + 2);

    if (isUnicodeScalarValue(code)) {
      return EscapeSequence { .value = std::to_wstring(code), .size = 6 };
    }

    // GraphQL allows JSON-style surrogate pair escape sequences, but only when
    // a valid pair is formed.
    if (isLeadingSurrogate(code)) {
      // \u
      if (
          body[position + 6] == 0x0000005c &&
          body[position + 7] == 0x00000075
         ) {
        int trailingCode = read16BitHexCode(body, position + 8);
        if (isTrailingSurrogate(trailingCode)) {
          // JavaScript defines strings as a sequence of UTF-16 code units and
          // encodes Unicode code points above U+FFFF using a surrogate pair of
          // code units. Since this is a surrogate pair escape sequence, just
          // include both codes into the JavaScript string value. Had JavaScript
          // not been internally based on UTF-16, then this surrogate pair would
          // be decoded to retrieve the supplementary code point.
          return EscapeSequence { .value = std::to_wstring(code) + std::to_wstring(trailingCode), .size = 12 };
        }
      }
    }

    std::wstring bodys = body.substr(position, position + 6);
    std::string s(bodys.begin(), bodys.end());

    throw GraphQLSyntaxError(
        lexer->source,
        position,
        "Invalid Unicode escape sequence: " + s + "."
        );
  }


  EscapeSequence readEscapedCharacter(Lexer *lexer, int position) {
    std::wstring body = lexer->source->body;
    wchar_t code = body[position + 1];
    switch (code) {
      case 0x00000022: // "
        return { .value = L"\u0022", .size = 2 };
      case 0x0000005c: // \.
        return { .value = L"\u005c", .size = 2 };
      case 0x0000002f: // /
        return { .value = L"\u002f", .size = 2 };
      case 0x00000062: // b
        return { .value = L"\u0008", .size = 2 };
      case 0x00000066: // f
        return { .value = L"\u000c", .size = 2 };
      case 0x0000006e: // n
        return { .value = L"\u000a", .size = 2 };
      case 0x00000072: // r
        return { .value = L"\u000d", .size = 2 };
      case 0x00000074: // t
        return { .value = L"\u0009", .size = 2 };
    }

    std::wstring bodys = body.substr(position, position + 2);
    std::string s(bodys.begin(), bodys.end());

    throw GraphQLSyntaxError(
        lexer->source,
        position,
        "Invalid character escape sequence: " + s + "."
        );
  }

  Token *readString(Lexer *lexer, int start) {
    std::wstring body = lexer->source->body;
    size_t bodyLength = body.size();
    int position = start + 1;
    int chunkStart = position;
    std::wstring value = L"";

    while (position < bodyLength) {
      wchar_t code = body[position];

      if (code == 0x00000022) {
        value += body.substr(chunkStart, position - chunkStart);
        return createToken(lexer, TokenKind::STRING, start, position + 1, value);
      }

      if (code == 0x0000005c) {
        value += body.substr(chunkStart, position - chunkStart);
        EscapeSequence escape =
          body[position + 1] == 0x00000075
          ? body[position + 2] == 0x0000007b
          ? readEscapedUnicodeVariableWidth(lexer, position)
          : readEscapedUnicodeFixedWidth(lexer, position)
          : readEscapedCharacter(lexer, position);
        value += escape.value;
        position += escape.size;
        chunkStart = position;
        continue;
      }

      if (code == 0x0000000a || code == 0x0000000d) {
        break;
      }

      if (isUnicodeScalarValue(code)) {
        ++position;
      } else if (isSupplementaryCodePoint(body, position)) {
        position += 2;
      } else {
        throw GraphQLSyntaxError(
            lexer->source,
            position,
            "Invalid character within String: " + printCodePointAt(
              lexer,
              position
              ) + "."
            );
      }
    }

    throw GraphQLSyntaxError(lexer->source, position, "Unterminated string.");
  }

  int readDigits(Lexer *lexer, int start, int firstCode) {
    if (std::iswdigit(firstCode) == 0) {
      throw GraphQLSyntaxError(
          lexer->source,
          start,
          "Invalid number, expected digit but got: " + printCodePointAt(
            lexer,
            start
            ) + "."
          );
    }

    std::wstring body = lexer->source->body;
    int position = start + 1; // +1 to skip first firstCode

    while (std::iswdigit(body[position]) != 0) {
      ++position;
    }

    return position;
  }


  bool isNameStart(wchar_t code) {
    return std::iswalpha(code) != 0 || code == 0x0000005f;
  }

  Token *readNumber(Lexer *lexer, int start, int firstCode) {
    std::wstring body = lexer->source->body;
    int position = start;
    int code = firstCode;
    bool isFloat = false;

    // NegativeSign (-)
    if (code == 0x0000002d) {
      code = body[++position];
    }

    // Zero (0)
    if (code == 0x00000030) {
      code = body[++position];
      if (std::iswdigit(code) != 0) {
        throw GraphQLSyntaxError(
            lexer->source,
            position,
            "Invalid number, unexpected digit after 0: " + printCodePointAt(
              lexer,
              position
              ) + "."
            );
      }
    } else {
      position = readDigits(lexer, position, code);
      code = body[position];
    }

    // Full stop (.)
    if (code == 0x0000002e) {
      isFloat = true;

      code = body[++position];
      position = readDigits(lexer, position, code);
      code = body[position];
    }

    // E e
    if (code == 0x00000045 || code == 0x00000065) {
      isFloat = true;

      code = body[++position];
      // + -
      if (code == 0x0000002b || code == 0x0000002d) {
        code = body[++position];
      }
      position = readDigits(lexer, position, code);
      code = body[position];
    }

    // Numbers cannot be followed by . or NameStart
    if (code == 0x0000002e || isNameStart(code)) {
      throw GraphQLSyntaxError(
          lexer->source,
          position,
          "Invalid number, expected digit but got: " + printCodePointAt(
            lexer,
            position
            ) + "."
          );
    }

    return createToken(
        lexer,
        isFloat ? TokenKind::FLOAT : TokenKind::INT,
        start,
        position,
        body.substr(start, position - start)
        );
  }

  bool isNameContinue(wchar_t code) {
    return std::iswalpha(code) != 0 || std::iswdigit(code) != 0 || code == 0x0000005f;
  }

  Token *readName(Lexer *lexer, int start) {
    std::wstring body = lexer->source->body;
    size_t bodyLength = body.size();
    int position = start + 1;

    while (position < bodyLength) {
      wchar_t code = body[position];
      if (isNameContinue(code)) {
        ++position;
      } else {
        break;
      }
    }

    return createToken(
        lexer,
        TokenKind::NAME,
        start,
        position,
        body.substr(start, position - start)
        );
  }

  Token *readNextToken(Lexer *lexer, int start) {
    std::wstring body = lexer->source->body;
    size_t bodyLength = body.size();
    int position = start;

    while (position < bodyLength) {
      wchar_t code = body[position];

      switch (code) {
        case 0x0000feff:
        case 0x00000009:
        case 0x00000020:
        case 0x0000002c:
          ++position;
          continue;
        case 0x0000000a:
          ++position;
          ++lexer->line;
          lexer->lineStart = position;
          continue;
        case 0x0000000d:
          if (body[position + 1] == 0x0000000a) {
            position += 2;
          } else {
            ++position;
          }
          ++lexer->line;
          lexer->lineStart = position;
          continue;
        case 0x00000023:
          return readComment(lexer, position);
        case 0x00000021:
          return createToken(lexer, TokenKind::BANG, position, position + 1);
        case 0x00000024:
          return createToken(lexer, TokenKind::DOLLAR, position, position + 1);
        case 0x00000026:
          return createToken(lexer, TokenKind::AMP, position, position + 1);
        case 0x00000028:
          return createToken(lexer, TokenKind::PAREN_L, position, position + 1);
        case 0x00000029:
          return createToken(lexer, TokenKind::PAREN_R, position, position + 1);
        case 0x0000002e:
          if (
              body[position + 1] == 0x0000002e &&
              body[position + 2] == 0x0000002e
             ) {
            return createToken(lexer, TokenKind::SPREAD, position, position + 3);
          }
          break;
        case 0x0000003a:
          return createToken(lexer, TokenKind::COLON, position, position + 1);
        case 0x0000003d:
          return createToken(lexer, TokenKind::EQUALS, position, position + 1);
        case 0x00000040:
          return createToken(lexer, TokenKind::AT, position, position + 1);
        case 0x0000005b:
          return createToken(lexer, TokenKind::BRACKET_L, position, position + 1);
        case 0x0000005d:
          return createToken(lexer, TokenKind::BRACKET_R, position, position + 1);
        case 0x0000007b:
          return createToken(lexer, TokenKind::BRACE_L, position, position + 1);
        case 0x0000007c:
          return createToken(lexer, TokenKind::PIPE, position, position + 1);
        case 0x0000007d:
          return createToken(lexer, TokenKind::BRACE_R, position, position + 1);
        case 0x0000003f:
          return createToken(
              lexer,
              TokenKind::QUESTION_MARK,
              position,
              position + 1
              );
        case 0x00000022:
          if (
              body[position + 1] == 0x00000022 &&
              body[position + 2] == 0x00000022
             ) {
            return readBlockString(lexer, position);
          }
          return readString(lexer, position);
      }

      if (iswdigit(code) != 0 || code == 0x0000002d) {
        return readNumber(lexer, position, code);
      }

      if (isNameStart(code)) {
        return readName(lexer, position);
      }

      throw GraphQLSyntaxError(
          lexer->source,
          position,
          code == 0x00000027
          ? "Unexpected single quote character (\'), did you mean to use a double quote (\")?"
          : isUnicodeScalarValue(code) || isSupplementaryCodePoint(body, position)
          ? "Unexpected character: " + printCodePointAt(lexer, position) + "."
          : "Invalid character: " + printCodePointAt(lexer, position) + "."
          );
    }

    return createToken(lexer, TokenKind::EOF, bodyLength, bodyLength);
  }

  enum class Kind {
    /** Name */
    NAME,

    /** Document */
    DOCUMENT,
    OPERATION_DEFINITION,
    VARIABLE_DEFINITION,
    SELECTION_SET,
    FIELD,
    ARGUMENT,

    /** Nullability Modifiers */
    LIST_NULLABILITY_OPERATOR,
    NON_NULL_ASSERTION,
    ERROR_BOUNDARY,

    /** Fragments */
    FRAGMENT_SPREAD,
    INLINE_FRAGMENT,
    FRAGMENT_DEFINITION,

    /** Values */
    VARIABLE,
    INT,
    FLOAT,
    STRING,
    BOOLEAN,
    NULL,
    ENUM,
    LIST,
    OBJECT,
    OBJECT_FIELD,

    /** Directives */
    DIRECTIVE,

    /** Types */
    NAMED_TYPE,
    LIST_TYPE,
    NON_NULL_TYPE,

    /** Type System Definitions */
    SCHEMA_DEFINITION,
    OPERATION_TYPE_DEFINITION,

    /** Type Definitions */
    SCALAR_TYPE_DEFINITION,
    OBJECT_TYPE_DEFINITION,
    FIELD_DEFINITION,
    INPUT_VALUE_DEFINITION,
    INTERFACE_TYPE_DEFINITION,
    UNION_TYPE_DEFINITION,
    ENUM_TYPE_DEFINITION,
    ENUM_VALUE_DEFINITION,
    INPUT_OBJECT_TYPE_DEFINITION,

    /** Directive Definitions */
    DIRECTIVE_DEFINITION,

    /** Type System Extensions */
    SCHEMA_EXTENSION,

    /** Type Extensions */
    SCALAR_TYPE_EXTENSION,
    OBJECT_TYPE_EXTENSION,
    INTERFACE_TYPE_EXTENSION,
    UNION_TYPE_EXTENSION,
    ENUM_TYPE_EXTENSION,
    INPUT_OBJECT_TYPE_EXTENSION,
  };

  enum class OperationTypeNode {
    QUERY,
    MUTATION,
    SUBSCIPTION
  };

  class ParseOptions {
    public:
      bool noLocation;
      int maxTokens;
      bool allowLegacyFragmentVariables;
      bool experimentalClientControlledNullability;
  };

  class ASTNode {
    public:
      Kind kind;
      Location *loc;
  };

  class DefinitionNode : public ASTNode {
    public:
      virtual ~DefinitionNode() = default;
  };

  class ExecutableDefinitionNode : public DefinitionNode {

  };

  class TypeSystemDefinitionNode : public DefinitionNode {
  };

  class TypeSystemExtensionNode : public DefinitionNode {
  };

  class SchemaExtensionNode : public TypeSystemExtensionNode {
  };

  class TypeExtensionNode : public TypeSystemExtensionNode {
  };

  class ScalarTypeExtensionNode : public TypeExtensionNode {
  };

  class ObjectTypeExtensionNode : public TypeExtensionNode {
  };
  class InterfaceTypeExtensionNode : public TypeExtensionNode {
  };
  class UnionTypeExtensionNode : public TypeExtensionNode {
  };
  class EnumTypeExtensionNode : public TypeExtensionNode {
  };
  class InputObjectTypeExtensionNode : public TypeExtensionNode {
  };
  class TypeDefinitionNode : public TypeSystemDefinitionNode {
  };

  class NameNode : public ASTNode {
    public:
      Kind kind;
      Location *loc;
      std::wstring value;

      NameNode(Kind kind, std::wstring value) {
        this->kind = kind;
        this->value = value;
      }
  };

  class DocumentNode : public ASTNode {
    public:
      Kind kind;
      Location *loc;
      std::vector<std::unique_ptr<DefinitionNode>> definitions;

      DocumentNode(Kind kind, std::vector<std::unique_ptr<DefinitionNode>> definitions) {
        this->kind = kind;
        this->definitions = std::move(definitions);
      }
  };

  class TypeNode : public ASTNode {
  };

  class NamedTypeNode : public TypeNode {
    public:
      Kind kind;
      Location *loc;
      std::unique_ptr<NameNode> name;

      NamedTypeNode(Kind kind, std::unique_ptr<NameNode> name) {
        this->kind = kind;
        this->name = std::move(name);
      }
  };

  class ListTypeNode : public TypeNode {
    public:
      Kind kind;
      std::unique_ptr<TypeNode> type;

      ListTypeNode(Kind kind, std::unique_ptr<TypeNode> type) {
        this->kind = kind;
        this->type = std::move(type);
      }
  };

  class NonNullTypeNode : public TypeNode {
    public:
      Kind kind;
      std::unique_ptr<TypeNode> type;

      NonNullTypeNode(Kind kind, std::unique_ptr<TypeNode> type) {
        this->kind = kind;
        this->type = std::move(type);
      }
  };

  class ValueNodeBase : public ASTNode {
    public:
      virtual ~ValueNodeBase() = default;
  };

  class ConstValueNode : virtual public ValueNodeBase {
  };

  class ArgumentNodeBase : public ASTNode {
  };

  class ObjectFieldNodeBase : public ASTNode {
    public:
      Location *loc;

      virtual ~ObjectFieldNodeBase() = default;
  };

  class ObjectFieldNode : public ObjectFieldNodeBase {
    public:
      Kind kind;
      std::unique_ptr<NameNode> name;
      std::unique_ptr<ValueNodeBase> value;

      ObjectFieldNode(Kind kind, std::unique_ptr<NameNode> name, std::unique_ptr<ValueNodeBase> value) {
        this->kind = kind;
        this->name = std::move(name);
        this->value = std::move(value);
      }

      ObjectFieldNode(const ObjectFieldNode& c) {
        this->kind = c.kind;
        this->name = std::make_unique<NameNode>(*c.name);
        this->value = std::make_unique<ValueNodeBase>(*c.value);
      }

  };

  class ConstObjectFieldNode : public ObjectFieldNodeBase {
    public:
      Kind kind;
      std::unique_ptr<NameNode> name;
      std::unique_ptr<ConstValueNode> value;

      ConstObjectFieldNode(Kind kind, std::unique_ptr<NameNode> name, std::unique_ptr<ConstValueNode> value) {
        this->kind = kind;
        this->name = std::move(name);
        this->value = std::move(value);
      }

      ConstObjectFieldNode(Kind kind, std::unique_ptr<ConstValueNode> value) {
        this->kind = kind;
        this->value = std::move(value);
      }

      ConstObjectFieldNode(const ConstObjectFieldNode& c) {
        this->kind = c.kind;
        this->name = std::make_unique<NameNode>(*c.name);
        this->value = std::make_unique<ConstValueNode>(*c.value);
      }
  };

  class ConstArgumentNode : public ArgumentNodeBase {
    public:
      Kind kind;
      Location *loc;
      NameNode name;
      ConstValueNode value;
  };

  class ConstDirectiveNode : public ASTNode {
    public:
      Kind kind;
      Location *loc;
      NameNode name;
      std::vector<ConstArgumentNode> arguments;
  };

  class VariableNode : public ValueNodeBase {
    public:
      Kind kind;
      Location *loc;
      std::unique_ptr<NameNode> name;

      VariableNode(Kind kind, std::unique_ptr<NameNode> name) {
        this->kind = kind;
        this->name = std::move(name);
      }
  };

  class VariableDefinitionNode : public ASTNode {
    public:
      Kind kind;
      std::unique_ptr<VariableNode> variable;
      std::unique_ptr<TypeNode> type;
      std::unique_ptr<ConstValueNode> defaultValue;
      std::vector<std::unique_ptr<ConstDirectiveNode>> directives;

      VariableDefinitionNode(Kind kind, std::unique_ptr<VariableNode> variable, std::unique_ptr<TypeNode> type, std::unique_ptr<ConstValueNode> defaultValue, std::vector<std::unique_ptr<ConstDirectiveNode>> directives) {
        this->kind = kind;
        this->variable = std::move(variable);
        this->type = std::move(type);
        this->defaultValue = std::move(defaultValue);
        this->directives = std::move(directives);
      }
  };

  class SelectionNode : public ASTNode {
    public:
      virtual ~SelectionNode() = default;

  };

  class ValueNode : virtual public ValueNodeBase {
  };

  class ArgumentNode : public ArgumentNodeBase {
    public:
      Kind kind;
      Location *loc;
      std::unique_ptr<NameNode> name;
      std::unique_ptr<ValueNodeBase> value;

      ArgumentNode(Kind kind, std::unique_ptr<NameNode> name, std::unique_ptr<ValueNodeBase> value) {
        this->kind = kind;
        this->name = std::move(name);
        this->value = std::move(value);
      }
  };

  class DirectiveNode : public ASTNode {
    public:
      Kind kind;
      Location *loc;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<ArgumentNodeBase>> arguments;

      DirectiveNode(Kind kind, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<ArgumentNodeBase>> arguments) {
        this->kind = kind;
        this->name = std::move(name);
        this->arguments = std::move(arguments);
      }

      virtual ~DirectiveNode() = default;
  };

  class SelectionSetNode : public ASTNode {
    public:
      Kind kind;
      Location *loc;
      std::vector<std::unique_ptr<SelectionNode>> selections;

      SelectionSetNode(Kind kind, std::vector<std::unique_ptr<SelectionNode>> selections) {
        this->kind = kind;
        this->selections = std::move(selections);
      }
  };

  class OperationDefinitionNode : public ExecutableDefinitionNode {
    public:
      OperationTypeNode operation;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<VariableDefinitionNode>> variableDefinitions;
      std::vector<std::unique_ptr<DirectiveNode>> directives;
      std::unique_ptr<SelectionSetNode> selectionSet;

      OperationDefinitionNode(Kind kind, OperationTypeNode operation, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<VariableDefinitionNode>> variableDefinitions, std::vector<std::unique_ptr<DirectiveNode>> directives, std::unique_ptr<SelectionSetNode> selectionSet) {
        std::cout << "CALLED " << to_underlying(kind) << std::endl;
        this->kind = kind;
        this->operation = operation;
        this->name = std::move(name);
        this->variableDefinitions = std::move(variableDefinitions);
        this->directives = std::move(directives);
        this->selectionSet = std::move(selectionSet);
      };
  };

  class NullabilityAssertionNode : public ASTNode {
  };

  class NonNullAssertionNode : public NullabilityAssertionNode {
    public:
      Kind kind;
      std::unique_ptr<NullabilityAssertionNode> nullabilityAssertion;

      NonNullAssertionNode(Kind kind, std::unique_ptr<NullabilityAssertionNode> nullabilityAssertion) {
        this->kind = kind;
        this->nullabilityAssertion = std::move(nullabilityAssertion);
      }
  };

  class ErrorBoundaryNode : public NullabilityAssertionNode {
    public:
      Kind kind;
      std::unique_ptr<NullabilityAssertionNode> nullabilityAssertion;

      ErrorBoundaryNode(Kind kind, std::unique_ptr<NullabilityAssertionNode> nullabilityAssertion) {
        this->kind = kind;
        this->nullabilityAssertion = std::move(nullabilityAssertion);
      }
  };

  class ListNullabilityOperatorNode : public NullabilityAssertionNode {
    public:
      Kind kind;
      std::unique_ptr<NullabilityAssertionNode> nullabilityAssertion;

      ListNullabilityOperatorNode(Kind kind, std::unique_ptr<NullabilityAssertionNode> nullabilityAssertion) {
        this->kind = kind;
        this->nullabilityAssertion = std::move(nullabilityAssertion);
      }
  };

  class FieldNode : public SelectionNode {
    public:
      Kind kind;
      std::unique_ptr<NameNode> alias;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<ArgumentNodeBase>> arguments; // TODO ArgumentNode
      std::unique_ptr<NullabilityAssertionNode> nullabilityAssertion;
      std::vector<std::unique_ptr<DirectiveNode>> directives;
      std::unique_ptr<SelectionSetNode> selectionSet;

      FieldNode(Kind kind, std::unique_ptr<NameNode> alias, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<ArgumentNodeBase>> arguments, std::unique_ptr<NullabilityAssertionNode> nullabilityAssertion, std::vector<std::unique_ptr<DirectiveNode>> directives, std::unique_ptr<SelectionSetNode> selectionSet) {
        this->kind = kind;
        this->alias = std::move(alias);
        this->name = std::move(name);
        this->arguments = std::move(arguments);
        this->nullabilityAssertion = std::move(nullabilityAssertion);
        this->directives = std::move(directives);
        this->selectionSet = std::move(selectionSet);
      }
  };

  class FragmentSpreadNode : public SelectionNode {
    public:
      Kind kind;
      Location *loc;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<DirectiveNode>> directives;

      FragmentSpreadNode(Kind kind, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<DirectiveNode>> directives) {
        this->kind = kind;
        this->name = std::move(name);
        this->directives = std::move(directives);
      }
  };

  class InlineFragmentNode : public SelectionNode {
    public:
      Kind kind;
      Location *loc;
      std::unique_ptr<NamedTypeNode> typeCondition;
      std::vector<std::unique_ptr<DirectiveNode>> directives;
      std::unique_ptr<SelectionSetNode> selectionSet;

      InlineFragmentNode(Kind kind, std::unique_ptr<NamedTypeNode> typeCondition, std::vector<std::unique_ptr<DirectiveNode>> directives, std::unique_ptr<SelectionSetNode> selectionSet) {
        this->kind = kind;
        this->typeCondition = std::move(typeCondition);
        this->directives = std::move(directives);
        this->selectionSet = std::move(selectionSet);
      }
  };

  bool isPunctuatorTokenKind(TokenKind kind) {
    return (
        kind == TokenKind::BANG ||
        kind == TokenKind::QUESTION_MARK ||
        kind == TokenKind::DOLLAR ||
        kind == TokenKind::AMP ||
        kind == TokenKind::PAREN_L ||
        kind == TokenKind::PAREN_R ||
        kind == TokenKind::SPREAD ||
        kind == TokenKind::COLON ||
        kind == TokenKind::EQUALS ||
        kind == TokenKind::AT ||
        kind == TokenKind::BRACKET_L ||
        kind == TokenKind::BRACKET_R ||
        kind == TokenKind::BRACE_L ||
        kind == TokenKind::PIPE ||
        kind == TokenKind::BRACE_R
        );
  }

  std::string getTokenKindStr(TokenKind kind) {
    switch (kind) {
      case TokenKind::SOF:
        return "<SOF>";
      case TokenKind::EOF:
        return "<EOF>";
      case TokenKind::BANG:
        return "!";
      case TokenKind::QUESTION_MARK:
        return "?";
      case TokenKind::DOLLAR:
        return "$";
      case TokenKind::AMP:
        return "&";
      case TokenKind::PAREN_L:
        return "(";
      case TokenKind::PAREN_R:
        return ")";
      case TokenKind::SPREAD:
        return "...";
      case TokenKind::COLON:
        return ":";
      case TokenKind::EQUALS:
        return "=";
      case TokenKind::AT:
        return "@";
      case TokenKind::BRACKET_L:
        return "[";
      case TokenKind::BRACKET_R:
        return "]";
      case TokenKind::BRACE_L:
        return "{";
      case TokenKind::PIPE:
        return "|";
      case TokenKind::BRACE_R:
        return "}";
      case TokenKind::NAME:
        return "Name";
      case TokenKind::INT:
        return "Int";
      case TokenKind::FLOAT:
        return "Float";
      case TokenKind::STRING:
        return "String";
      case TokenKind::BLOCK_STRING:
        return "BlockString";
      case TokenKind::COMMENT:
        return "Comment";

    }
  }

  std::string getTokenKindDesc(TokenKind kind) {
    return getTokenKindStr(kind);
  }

  std::string getTokenDesc(Token *token) {
    auto value = token->value;
    std::string valueStr(value.begin(), value.end());
    return getTokenKindDesc(token->kind) + " " + valueStr; // TODO if valueStr == "" omit
  }

  class ListValueNode : public ValueNode {
    public:
      Kind kind;
      Location *loc;
      std::vector<std::unique_ptr<ValueNodeBase>> values;

      ListValueNode(Kind kind, std::vector<std::unique_ptr<ValueNodeBase>> values) {
        this->kind = kind;
        this->values = std::move(values);
      }
  };

  class ObjectValueNodeBase : public ValueNode {
    public:
      Location *loc;
  };

  class ObjectValueNode : public ObjectValueNodeBase {
    public:
      Kind kind;
      std::vector<std::unique_ptr<ObjectFieldNode>> values;

      ObjectValueNode(Kind kind, std::vector<std::unique_ptr<ObjectFieldNode>> values) {
        this->kind = kind;
        this->values = std::move(values);
      }
  };

  class ConstObjectValueNode : public ObjectValueNodeBase {
    public:
      Kind kind;
      std::vector<std::unique_ptr<ConstObjectFieldNode>> fields;

      ConstObjectValueNode(Kind kind, std::vector<std::unique_ptr<ConstObjectFieldNode>> fields) {
        this->kind = kind;
        this->fields = std::move(fields);
      }
  };

  class IntValueNode : public ValueNode, public ConstValueNode {
    public:
      Kind kind;
      Location *loc;
      std::wstring value;

      IntValueNode(Kind kind, std::wstring value) {
        this->kind = kind;
        this->value = value;
      }
  };

  class FloatValueNode : public ValueNode, public ConstValueNode {
    public:
      Kind kind;
      Location *loc;
      std::wstring value;

      FloatValueNode(Kind kind, std::wstring value) {
        this->kind = kind;
        this->value = value;
      }
  };

  class StringValueNode : public ValueNode, public ConstValueNode {
    public:
      Kind kind;
      Location *loc;
      std::wstring value;
      bool block;

      StringValueNode(Kind kind, std::wstring value, bool block) {
        this->kind = kind;
        this->value = value;
        this->block = block;
      }
  };
  class BooleanValueNode : public ValueNode, public ConstValueNode {
    public:
      Kind kind;
      bool value;

      BooleanValueNode(Kind kind, bool value) {
        this->kind = kind;
        this->value = value;
      }
  };
  class NullValueNode : public ValueNode, public ConstValueNode {
    public:
      Kind kind;

      NullValueNode(Kind kind) {
        this->kind = kind;
      }
  };
  class EnumValueNode : public ValueNode, ConstValueNode {
    public:
      Kind kind;
      std::wstring value;

      EnumValueNode(Kind kind, std::wstring value) {
        this->kind = kind;
        this->value = value;
      }
  };
  class ConstListValueNode: public ConstValueNode {
    public:
      Kind kind;
      std::vector<std::unique_ptr<ConstValueNode>> values;

      ConstListValueNode(Kind kind, std::vector<std::unique_ptr<ConstValueNode>> values) {
        this->kind = kind;
        this->values = std::move(values);
      }
  };

  class OperationTypeDefinitionNode : public ASTNode {
    public:
      Kind kind;
      OperationTypeNode operation;
      std::unique_ptr<NamedTypeNode> type;

      OperationTypeDefinitionNode(Kind kind, OperationTypeNode operation, std::unique_ptr<NamedTypeNode> type) {
        this->kind = kind;
        this->operation = operation;
        this->type = std::move(type);
      }
  };

  class SchemaDefinitionNode : public TypeSystemDefinitionNode {
    public:
      Kind kind;
      std::unique_ptr<StringValueNode> description;
      std::vector<std::unique_ptr<ConstDirectiveNode>> directives;
      std::vector<std::unique_ptr<OperationTypeDefinitionNode>> operationTypes;

      SchemaDefinitionNode(Kind kind, std::unique_ptr<StringValueNode> description, std::vector<std::unique_ptr<ConstDirectiveNode>> directives, std::vector<std::unique_ptr<OperationTypeDefinitionNode>> operationTypes) {
        this->kind = kind;
        this->description = std::move(description);
        this->directives = std::move(directives);
        this->operationTypes = std::move(operationTypes);
      }
  };

  class ScalarTypeDefinitioNode : public TypeDefinitionNode {
    public:
      Kind kind;
      std::unique_ptr<StringValueNode> description;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<ConstDirectiveNode>> directives;

      ScalarTypeDefinitioNode(Kind kind, std::unique_ptr<StringValueNode> description, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<ConstDirectiveNode>> directives) {
        this->kind = kind;
        this->description = std::move(description);
        this->name = std::move(name);
        this->directives = std::move(directives);
      }
  };

  class InputValueDefinitionNode : public ASTNode {
    public:
      Kind kind;
      std::unique_ptr<StringValueNode> description;
      std::unique_ptr<NameNode> name;
      std::unique_ptr<TypeNode> type;
      std::unique_ptr<ConstValueNode> defaultValue;
      std::vector<std::unique_ptr<ConstDirectiveNode>> directives;

      InputValueDefinitionNode(Kind kind, std::unique_ptr<StringValueNode> description, std::unique_ptr<NameNode> name, std::unique_ptr<TypeNode> type, std::unique_ptr<ConstValueNode> defaultValue, std::vector<std::unique_ptr<ConstDirectiveNode>> directives) {
        this->kind = kind;
        this->description = std::move(description);
        this->name = std::move(name);
        this->type = std::move(type);
        this->defaultValue = std::move(defaultValue);
        this->directives = std::move(directives);
      }
  };

  class FieldDefinitionNode : public ASTNode {
    public:
      Kind kind;
      std::unique_ptr<StringValueNode> description;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<InputValueDefinitionNode>> arguments;
      std::unique_ptr<TypeNode> type;
      std::vector<std::unique_ptr<ConstDirectiveNode>> directives;

      FieldDefinitionNode(Kind kind, std::unique_ptr<StringValueNode> description, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<InputValueDefinitionNode>> arguments, std::unique_ptr<TypeNode> type, std::vector<std::unique_ptr<ConstDirectiveNode>> directives) {
        this->kind = kind;
        this->description = std::move(description);
        this->name = std::move(name);
        this->arguments = std::move(arguments);
        this->type = std::move(type);
        this->directives = std::move(directives);
      }
  };

  class EnumValueDefinitionNode : public ASTNode {
    public:
      Kind kind;
      std::unique_ptr<StringValueNode> description;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<ConstDirectiveNode>> directives;

      EnumValueDefinitionNode(Kind kind, std::unique_ptr<StringValueNode> description, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<ConstDirectiveNode>> directives) {
        this->kind = kind;
        this->description = std::move(description);
        this->name = std::move(name);
        this->directives = std::move(directives);
      }
  };

  class EnumTypeDefinitionNode : public TypeDefinitionNode {
    public:
      Kind kind;
      std::unique_ptr<StringValueNode> description;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<ConstDirectiveNode>> directives;
      std::vector<std::unique_ptr<EnumValueDefinitionNode>> values;

      EnumTypeDefinitionNode(Kind kind, std::unique_ptr<StringValueNode> description, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<ConstDirectiveNode>> directives, std::vector<std::unique_ptr<EnumValueDefinitionNode>> values) {
        this->kind = kind;
        this->description = std::move(description);
        this->name = std::move(name);
        this->directives = std::move(directives);
        this->values = std::move(values);
      }
  };

  class InterfaceTypeDefinitionNode : public TypeDefinitionNode {
    public:
      Kind kind;
      std::unique_ptr<StringValueNode> description;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<NamedTypeNode>> interfaces;
      std::vector<std::unique_ptr<ConstDirectiveNode>> directives;
      std::vector<std::unique_ptr<FieldDefinitionNode>> fields;

      InterfaceTypeDefinitionNode(Kind kind, std::unique_ptr<StringValueNode> description, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<NamedTypeNode>> interfaces, std::vector<std::unique_ptr<ConstDirectiveNode>> directives, std::vector<std::unique_ptr<FieldDefinitionNode>> fields) {
        this->kind = kind;
        this->description = std::move(description);
        this->name = std::move(name);
        this->interfaces = std::move(interfaces);
        this->directives = std::move(directives);
        this->fields = std::move(fields);
      }
  };


  class UnionTypeDefinitionNode : public TypeDefinitionNode {
    public:
      Kind kind;
      std::unique_ptr<StringValueNode> description;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<ConstDirectiveNode>> directives;
      std::vector<std::unique_ptr<NamedTypeNode>> types;

      UnionTypeDefinitionNode(Kind kind, std::unique_ptr<StringValueNode> description, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<ConstDirectiveNode>> directives, std::vector<std::unique_ptr<NamedTypeNode>> types) {
        this->kind = kind;
        this->description = std::move(description);
        this->name = std::move(name);
        this->directives = std::move(directives);
        this->types = std::move(types);
      }
  };

  class ObjectTypeDefinitionNode : public TypeDefinitionNode {
    public:
      Kind kind;
      std::unique_ptr<StringValueNode> description;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<NamedTypeNode>> interfaces;
      std::vector<std::unique_ptr<ConstDirectiveNode>> directives;
      std::vector<std::unique_ptr<FieldDefinitionNode>> fields;

      ObjectTypeDefinitionNode(Kind kind, std::unique_ptr<StringValueNode> description, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<NamedTypeNode>> interfaces, std::vector<std::unique_ptr<ConstDirectiveNode>> directives, std::vector<std::unique_ptr<FieldDefinitionNode>> fields) {
        this->kind = kind;
        this->description = std::move(description);
        this->name = std::move(name);
        this->interfaces = std::move(interfaces);
        this->directives = std::move(directives);
        this->fields = std::move(fields);
      }
  };

  class InputObjectTypeDefinitionNode : public TypeDefinitionNode {
    public:
      Kind kind;
      std::unique_ptr<StringValueNode> description;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<ConstDirectiveNode>> directives;
      std::vector<std::unique_ptr<InputValueDefinitionNode>> fields;

      InputObjectTypeDefinitionNode(Kind kind, std::unique_ptr<StringValueNode> description, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<ConstDirectiveNode>> directives, std::vector<std::unique_ptr<InputValueDefinitionNode>> fields) {
        this->kind = kind;
        this->description = std::move(description);
        this->name = std::move(name);
        this->directives = std::move(directives);
        this->fields = std::move(fields);
      }
  };

  class DirectiveDefinitionNode : public TypeSystemDefinitionNode {
    public:
      Kind kind;
      std::unique_ptr<StringValueNode> description;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<InputValueDefinitionNode>> arguments;
      bool repeatable;
      std::vector<std::unique_ptr<NameNode>> locations;

      DirectiveDefinitionNode(Kind kind, std::unique_ptr<StringValueNode> description, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<InputValueDefinitionNode>> arguments, bool repeatable, std::vector<std::unique_ptr<NameNode>> locations) {
        this->kind = kind;
        this->description = std::move(description);
        this->name = std::move(name);
        this->arguments = std::move(arguments);
        this->repeatable = repeatable;
        this->locations = std::move(locations);
      }
  };

  class FragmentDefinitionNode : public ExecutableDefinitionNode {
    public:
      Kind kind;
      std::unique_ptr<NameNode> name;
      std::vector<std::unique_ptr<VariableDefinitionNode>> variableDefinitions;
      std::unique_ptr<NamedTypeNode> typeCondition;
      std::vector<std::unique_ptr<DirectiveNode>> directives;
      std::unique_ptr<SelectionSetNode> selectionSet;

      FragmentDefinitionNode(Kind kind, std::unique_ptr<NameNode> name, std::vector<std::unique_ptr<VariableDefinitionNode>> variableDefinitions, std::unique_ptr<NamedTypeNode> typeCondition, std::vector<std::unique_ptr<DirectiveNode>> directives, std::unique_ptr<SelectionSetNode> selectionSet) {
        this->kind = kind;
        this->name = std::move(name);
        this->variableDefinitions = std::move(variableDefinitions);
        this->typeCondition = std::move(typeCondition);
        this->directives = std::move(directives);
        this->selectionSet = std::move(selectionSet);
      }

      FragmentDefinitionNode(Kind kind, std::unique_ptr<NameNode> name, std::unique_ptr<NamedTypeNode> typeCondition, std::vector<std::unique_ptr<DirectiveNode>> directives, std::unique_ptr<SelectionSetNode> selectionSet) {
        this->kind = kind;
        this->name = std::move(name);
        this->typeCondition = std::move(typeCondition);
        this->directives = std::move(directives);
        this->selectionSet = std::move(selectionSet);
      }
  };

  std::set<std::wstring> directiveLocation({L"QUERY", L"MUTATION", L"SUBSCRIPTION", L"FIELD", L"FRAGMENT_DEFINITION", L"FRAGMENT_SPREAD", L"INLINE_FRAGMENT", L"VARIABLE_DEFINITION", L"SCHEMA", L"SCALAR", L"OBJECT", L"FIELD_DEFINITION", L"ARGUMENT_DEFINITION", L"INTERFACE", L"UNION", L"ENUM", L"ENUM_VALUE", L"INPUT_OBJECT", L"INPUT_FIELD_DEFINITION"});

  class Parser {
    public:
      ParseOptions *options;
      Lexer *lexer;
      int tokenCounter;

      Parser(Source *source, ParseOptions *options = nullptr) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        this->lexer = new Lexer(source);
        this->options = options;
        this->tokenCounter = 0;
      }

      template<typename T>
        std::unique_ptr<T> node(Token *startToken, std::unique_ptr<T> node) {
#ifdef DEBUG
          std::cout << __func__ << std::endl;
#endif
          if (this->options == nullptr || this->options->noLocation != true)
            node->loc = new Location(startToken, this->lexer->lastToken, this->lexer->source);
          return node;
        }

      template<typename T>
        std::vector<std::unique_ptr<T>> many(TokenKind openKind, std::unique_ptr<T>(Parser::*parseFn)(), TokenKind closeKind) {
#ifdef DEBUG
          std::cout << __func__ << std::endl;
#endif
          this->expectToken(openKind);
          std::vector<std::unique_ptr<T>> result = std::vector<std::unique_ptr<T>>();
          do {
            result.push_back((this->*parseFn)());
          } while (!this->expectOptionalToken(closeKind));
          return result;
        }

      template<typename T>
        std::vector<std::unique_ptr<T>> optionalMany(TokenKind openKind, std::unique_ptr<T>(Parser::*parseFn)(), TokenKind closeKind) {
#ifdef DEBUG
          std::cout << __func__ << std::endl;
#endif
          if (this->expectOptionalToken(openKind)) {
            auto nodes = std::vector<std::unique_ptr<T>>();
            do {
              nodes.push_back((this->*parseFn)());
            } while (!this->expectOptionalToken(closeKind));
          }
          return std::vector<std::unique_ptr<T>>();
        }

      template<typename T>
        std::vector<std::unique_ptr<T>> delimitedMany(TokenKind delimiterKind, std::unique_ptr<T>(Parser::*parseFn)()) {
#ifdef DEBUG
          std::cout << __func__ << std::endl;
#endif
          this->expectOptionalToken(delimiterKind);
          auto nodes = std::vector<std::unique_ptr<T>>();
          do {
            nodes.push_back((this->*parseFn)());
          } while (this->expectOptionalToken(delimiterKind));
          return nodes;
        }

      template<typename T>
        std::vector<std::unique_ptr<T>> any(TokenKind openKind, std::unique_ptr<T>(Parser::*parseFn)(bool), TokenKind closeKind, bool isConst) {
#ifdef DEBUG
          std::cout << __func__ << std::endl;
#endif
          this->expectToken(openKind);
          auto nodes = std::vector<std::unique_ptr<T>>();
          while (!this->expectOptionalToken(closeKind))
            nodes.push_back((this->*parseFn)(isConst));
          return nodes;
        }

      void advanceLexer() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        int maxTokens = this->options != nullptr ? this->options->maxTokens : -1;
        Token *token = this->lexer->advance();

        if (maxTokens != -1 && token->kind != TokenKind::EOF) {
          ++this->tokenCounter;
          if (this->tokenCounter > maxTokens)
            throw GraphQLSyntaxError(this->lexer->source, token->start, "Document contains more than " + std::to_string(maxTokens) + " tokens. Parsing aborted.");
        }
      }

      bool expectOptionalToken(TokenKind kind) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *token = this->lexer->token;
        if (token->kind == kind) {
          this->advanceLexer();
          return true;
        }
        return false;
      }

      bool expectOptionalToken(std::wstring value) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *token = this->lexer->token;
        if (token->kind == TokenKind::NAME && token->value.compare(value) == 0) {
          this->advanceLexer();
          return true;
        }
        return false;
      }

      bool expectOptionalKeyword(std::wstring value) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto token = this->lexer->token;
        if (token->kind == TokenKind::NAME && token->value.compare(value) == 0) {
          this->advanceLexer();
          return true;
        }
        return false;
      }

      Token *expectToken(TokenKind kind) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *token = this->lexer->token;
        if (token->kind == kind) {
          this->advanceLexer();
          return token;
        }

        throw GraphQLSyntaxError(this->lexer->source, token->start, "Expected " + getTokenKindDesc(kind) + ", found " + getTokenDesc(token) + ".");
      }

      void expectKeyword(std::wstring value) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *token = this->lexer->token;
        if (token->kind == TokenKind::NAME && token->value.compare(value) == 0)
          this->advanceLexer();
        else {
          std::string valueStr(value.begin(), value.end());
          throw GraphQLSyntaxError(this->lexer->source, token->start, "Expected " + valueStr + ", found " + getTokenDesc(token) + ".");
        }
      }

      bool peek(TokenKind kind) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->lexer->token->kind == kind;
      }

      bool peekDescription() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->peek(TokenKind::STRING) || this->peek(TokenKind::BLOCK_STRING);
      }

      GraphQLError unexpected(Token *atToken = nullptr) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *token = atToken ? atToken : this->lexer->token;
        return GraphQLSyntaxError(this->lexer->source, token->start, "Unexpected " + getTokenDesc(token) + ".");
      }

      std::unique_ptr<DefinitionNode> parseDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        if (this->peek(TokenKind::BRACE_L))
          return this->parseOperationDefinition();

        bool hasDescription = this->peekDescription();
        Token *keywordToken = hasDescription ? this->lexer->lookahead() : this->lexer->token;

        if (keywordToken->kind == TokenKind::NAME) {
          if (keywordToken->value == L"schema")
            return this->parseSchemaDefinition();
          if (keywordToken->value == L"scalar")
            return this->parseScalarTypeDefinition();
          if (keywordToken->value == L"type")
            return this->parseObjectTypeDefinition();
          if (keywordToken->value == L"interface")
            return this->parseInterfaceTypeDefinition();
          if (keywordToken->value == L"union")
            return this->parseUnionTypeDefinition();
          if (keywordToken->value == L"enum")
            return this->parseEnumTypeDefinition();
          if (keywordToken->value == L"input")
            return this->parseInputObjectTypeDefinition();
          if (keywordToken->value == L"directive")
            return this->parseDirectiveDefinition();

          if (hasDescription) {
            throw GraphQLSyntaxError(this->lexer->source, this->lexer->token->start, "Unexpected description, descriptions are supported only on type definitions.");
          }

          if (keywordToken->value == L"query" || keywordToken->value == L"mutation" || keywordToken->value == L"subscription")
            return this->parseOperationDefinition();
          if (keywordToken->value == L"fragment")
            return this->parseFragmentDefinition();
          if (keywordToken->value == L"extend")
            return this->parseTypeSystemExtension();
        }

        throw this->unexpected(keywordToken);
      }

      std::unique_ptr<OperationDefinitionNode> parseOperationDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *start = this->lexer->token;
        if (this->peek(TokenKind::BRACE_L)) {
          return this->node<OperationDefinitionNode>(start, std::make_unique<OperationDefinitionNode>(Kind::OPERATION_DEFINITION, OperationTypeNode::QUERY, nullptr, std::vector<std::unique_ptr<VariableDefinitionNode>>(), std::vector<std::unique_ptr<DirectiveNode>>(), this->parseSelectionSet()));
        }
        auto operation = this->parseOperationType();
        std::unique_ptr<NameNode> name = nullptr;
        if (this->peek(TokenKind::NAME))
          name = this->parseName();
        auto pv = this->parseVariableDefinitions();
        auto dir = this->parseDirectives(false);
        auto ss = this->parseSelectionSet();
        return this->node<OperationDefinitionNode>(start, std::make_unique<OperationDefinitionNode>(Kind::OPERATION_DEFINITION, operation, std::move(name), std::move(pv), std::move(dir), std::move(ss)));
      }

      std::vector<std::unique_ptr<VariableDefinitionNode>> parseVariableDefinitions() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->optionalMany<VariableDefinitionNode>(TokenKind::PAREN_L, &Parser::parseVariableDefinition, TokenKind::PAREN_R);
      }

      std::unique_ptr<VariableDefinitionNode> parseVariableDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->node<VariableDefinitionNode>(this->lexer->token, std::make_unique<VariableDefinitionNode>(Kind::VARIABLE_DEFINITION, this->parseVariable(), (this->expectToken(TokenKind::COLON), this->parseTypeReference()), this->expectOptionalToken(TokenKind::EQUALS) ? this->parseConstValueLiteral() : nullptr, this->parseConstDirectives()));
      }

      std::unique_ptr<ConstValueNode> parseConstValueLiteral() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return std::make_unique<ConstValueNode>(dynamic_cast<ConstValueNode&>(*this->parseValueLiteral(true)));
      }

      std::unique_ptr<TypeNode> parseTypeReference() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        std::unique_ptr<TypeNode> type;
        if (this->expectOptionalToken(TokenKind::BRACKET_L)) {
          auto innerType = this->parseTypeReference();
          this->expectToken(TokenKind::BRACKET_R);
          type = this->node<ListTypeNode>(start, std::make_unique<ListTypeNode>(Kind::LIST_TYPE, std::move(innerType)));
        } else
          type = this->parseNamedType();

        if (this->expectOptionalToken(TokenKind::BANG)) {
          return this->node<NonNullTypeNode>(start, std::make_unique<NonNullTypeNode>(Kind::NON_NULL_TYPE, std::move(type)));
        }

        return type;
      }

      std::unique_ptr<NameNode> parseName() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *token = expectToken(TokenKind::NAME);
        return this->node<NameNode>(token, std::make_unique<NameNode>(Kind::NAME, token->value));
      }

      std::unique_ptr<DocumentNode> parseDocument() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->node<DocumentNode>(this->lexer->token, std::make_unique<DocumentNode>(Kind::DOCUMENT, this->many<DefinitionNode>(TokenKind::SOF, &Parser::parseDefinition, TokenKind::EOF)));
      }

      std::unique_ptr<SelectionSetNode> parseSelectionSet() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->node<SelectionSetNode>(this->lexer->token, std::make_unique<SelectionSetNode>(Kind::SELECTION_SET, this->many<SelectionNode>(TokenKind::BRACE_L, &Parser::parseSelection, TokenKind::BRACE_R)));
      }

      std::unique_ptr<SelectionNode> parseSelection() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->peek(TokenKind::SPREAD) ? this->parseFragment() : this->parseField();
      }

      std::unique_ptr<FieldNode> parseField() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *start = this->lexer->token;
        std::unique_ptr<NameNode> nameOrAlias = this->parseName();
        std::unique_ptr<NameNode> alias = nullptr;
        std::unique_ptr<NameNode> name = nullptr;
        if (this->expectOptionalToken(TokenKind::COLON)) {
          alias = std::move(nameOrAlias);
          name = this->parseName();
        } else
          name = std::move(nameOrAlias);

        auto args = this->parseArguments(false);
        auto null = this->parseNullabilityAssertion();
        auto dir = this->parseDirectives(false);
        std::unique_ptr<SelectionSetNode> ss = nullptr;
        if (this->peek(TokenKind::BRACE_L))
          ss = this->parseSelectionSet();
        return this->node<FieldNode>(start, std::make_unique<FieldNode>(Kind::FIELD, std::move(alias), std::move(name), std::move(args), std::move(null), std::move(dir), this->peek(TokenKind::BRACE_L) ? std::move(ss) : nullptr));
      }

      std::unique_ptr<NullabilityAssertionNode> parseNullabilityAssertion() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        if (this->options != nullptr && !this->options->experimentalClientControlledNullability)
          return nullptr;

        auto start = this->lexer->token;
        std::unique_ptr<NullabilityAssertionNode> nullabilityAssertion;

        if (this->expectOptionalToken(TokenKind::BRACKET_L)) {
          auto innerModifier = this->parseNullabilityAssertion();
          this->expectToken(TokenKind::BRACKET_R);
          nullabilityAssertion = this->node<ListNullabilityOperatorNode>(start, std::make_unique<ListNullabilityOperatorNode>(Kind::LIST_NULLABILITY_OPERATOR, std::move(innerModifier)));
        }

        if (this->expectOptionalToken(TokenKind::BANG)) {
          nullabilityAssertion = this->node<NonNullAssertionNode>(start, std::make_unique<NonNullAssertionNode>(Kind::NON_NULL_ASSERTION, std::move(nullabilityAssertion)));
        } else if (this->expectOptionalToken(TokenKind::QUESTION_MARK)) {
          nullabilityAssertion = this->node<ErrorBoundaryNode>(start, std::make_unique<ErrorBoundaryNode>(Kind::ERROR_BOUNDARY, std::move(nullabilityAssertion)));
        }

        return nullabilityAssertion;
      }

      std::unique_ptr<SelectionNode> parseFragment() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *start = this->lexer->token;
        this->expectToken(TokenKind::SPREAD);

        bool hasTypeCondition = this->expectOptionalToken(L"on");
        if (!hasTypeCondition && this->peek(TokenKind::NAME)) {
          return this->node<FragmentSpreadNode>(start, std::make_unique<FragmentSpreadNode>(Kind::FRAGMENT_SPREAD, this->parseFragmentName(), this->parseDirectives(false)));
        }
        return this->node<InlineFragmentNode>(start, std::make_unique<InlineFragmentNode>(Kind::INLINE_FRAGMENT, hasTypeCondition ? this->parseNamedType() : nullptr, this->parseDirectives(false), this->parseSelectionSet()));
      }

      std::unique_ptr<NamedTypeNode> parseNamedType() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->node<NamedTypeNode>(this->lexer->token, std::make_unique<NamedTypeNode>(Kind::NAMED_TYPE, this->parseName()));
      }

      std::unique_ptr<NameNode> parseFragmentName() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        if (this->lexer->token->value.compare(L"on") == 0)
          throw this->unexpected();
        return this->parseName();
      }

      std::vector<std::unique_ptr<DirectiveNode>> parseDirectives(bool isConst) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto directives = std::vector<std::unique_ptr<DirectiveNode>>();
        while (this->peek(TokenKind::AT))
          directives.push_back(this->parseDirective(isConst));
        return directives;
      }

      std::unique_ptr<DirectiveNode> parseDirective(bool isConst) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *start = this->lexer->token;
        this->expectToken(TokenKind::AT);
        return this->node<DirectiveNode>(start, std::make_unique<DirectiveNode>(Kind::DIRECTIVE, this->parseName(), this->parseArguments(isConst)));
      }

      std::vector<std::unique_ptr<ArgumentNodeBase>> parseArguments(bool isConst) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto (Parser::*parseArgumentPtr)() = &Parser::parseArgument;
        return this->optionalMany<ArgumentNodeBase>(TokenKind::PAREN_L, isConst ? &Parser::parseConstArgument : parseArgumentPtr, TokenKind::PAREN_R);
      }

      std::unique_ptr<ArgumentNodeBase> parseArgument() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->parseArgument(false);
      }

      std::unique_ptr<ArgumentNodeBase> parseArgument(bool isConst) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *start = this->lexer->token;
        auto name = this->parseName();
        this->expectToken(TokenKind::COLON);
        return this->node<ArgumentNode>(start, std::make_unique<ArgumentNode>(Kind::ARGUMENT, std::move(name), this->parseValueLiteral(isConst)));
      }

      std::unique_ptr<ArgumentNodeBase> parseConstArgument() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->parseArgument(true);
      }

      std::unique_ptr<ValueNodeBase> parseValueLiteral(bool isConst) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *token = this->lexer->token;
        switch (token->kind) {
          case TokenKind::BRACKET_L:
            return this->parseList(isConst);
          case TokenKind::BRACE_L:
            return this->parseObject(isConst);
          case TokenKind::INT:
            this->advanceLexer();
            return this->node<IntValueNode>(token, std::make_unique<IntValueNode>(Kind::INT, token->value));
          case TokenKind::FLOAT:
            this->advanceLexer();
            return this->node<FloatValueNode>(token, std::make_unique<FloatValueNode>(Kind::FLOAT, token->value));
          case TokenKind::STRING:
          case TokenKind::BLOCK_STRING:
            this->parseStringLiteral();
          case TokenKind::NAME:
            this->advanceLexer();
            if (token->value.compare(L"true") == 0) return this->node<BooleanValueNode>(token, std::make_unique<BooleanValueNode>(Kind::BOOLEAN, L"true"));
            if (token->value.compare(L"false") == 0) return this->node<BooleanValueNode>(token, std::make_unique<BooleanValueNode>(Kind::BOOLEAN, L"false"));
            if (token->value.compare(L"null") == 0) return this->node<NullValueNode>(token, std::make_unique<NullValueNode>(Kind::NULL));
            return this->node<EnumValueNode>(token, std::make_unique<EnumValueNode>(Kind::ENUM, token->value));
          case TokenKind::DOLLAR:
            if (isConst) {
              this->expectToken(TokenKind::DOLLAR);
              if (this->lexer->token->kind == TokenKind::NAME) {
                std::wstring varName = this->lexer->token->value;
                std::string varNameAscii(varName.begin(), varName.end());
                throw GraphQLSyntaxError(this->lexer->source, token->start, "Unexpected variable " + varNameAscii + " in constant value.");
              } else {
                throw this->unexpected(token);
              }
            }
            return this->parseVariable();
          default:
            throw this->unexpected();
        }
      }

      std::unique_ptr<VariableNode> parseVariable() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *start = this->lexer->token;
        this->expectToken(TokenKind::DOLLAR);
        return this->node<VariableNode>(start, std::make_unique<VariableNode>(Kind::VARIABLE, this->parseName()));
      }

      std::unique_ptr<StringValueNode> parseStringLiteral() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *token = this->lexer->token;
        this->advanceLexer();
        return this->node<StringValueNode>(token, std::make_unique<StringValueNode>(Kind::STRING, token->value, token->kind == TokenKind::BLOCK_STRING));
      }

      std::unique_ptr<ValueNodeBase> parseList(bool isConst) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        /*
           if (isConst) {
           auto any = this->any<ValueNodeBase>(TokenKind::BRACKET_L, &Parser::parseValueLiteral, TokenKind::BRACKET_R, isConst);
           auto anyConst = std::vector<std::unique_ptr<ConstValueNode>>();
           for (auto& a : any)
           anyConst.push_back(std::make_unique<ConstValueNode>(dynamic_cast<ConstValueNode&>(*a)));
           return this->node<ConstListValueNode>(this->lexer->token, std::make_unique<ConstListValueNode>(Kind::LIST, std::move(anyConst)));
           } else {
           auto any = this->any<ValueNodeBase>(TokenKind::BRACKET_L, &Parser::parseValueLiteral, TokenKind::BRACKET_R, isConst);
           auto anyNonConst = std::vector<std::unique_ptr<ValueNode>>();
           for (auto& a : any)
           anyNonConst.push_back(std::make_unique<ValueNode>(dynamic_cast<ValueNode&>(*a)));
           return this->node<ListValueNode>(this->lexer->token, std::make_unique<ListValueNode>(Kind::LIST, std::move(anyNonConst)));
           }
           */
        auto any = this->any<ValueNodeBase>(TokenKind::BRACKET_L, &Parser::parseValueLiteral, TokenKind::BRACKET_R, false);
        return this->node<ListValueNode>(this->lexer->token, std::make_unique<ListValueNode>(Kind::LIST, std::move(any)));
      }

      std::unique_ptr<ObjectValueNodeBase> parseObject(bool isConst) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        if (isConst) {
          auto any = this->any<ObjectFieldNodeBase>(TokenKind::BRACE_L, &Parser::parseObjectField, TokenKind::BRACE_R, isConst);
          auto anyConst = std::vector<std::unique_ptr<ConstObjectFieldNode>>();
          for (auto& a : any)
            anyConst.push_back(std::make_unique<ConstObjectFieldNode>(dynamic_cast<ConstObjectFieldNode&>(*a)));
          return this->node<ConstObjectValueNode>(this->lexer->token, std::make_unique<ConstObjectValueNode>(Kind::OBJECT, std::move(anyConst)));
        } else {
          auto any = this->any<ObjectFieldNodeBase>(TokenKind::BRACE_L, &Parser::parseObjectField, TokenKind::BRACE_R, isConst);
          auto anyNonConst = std::vector<std::unique_ptr<ObjectFieldNode>>();
          for (auto& a : any)
            anyNonConst.push_back(std::make_unique<ObjectFieldNode>(dynamic_cast<ObjectFieldNode&>(*a)));
          return this->node<ObjectValueNode>(this->lexer->token, std::make_unique<ObjectValueNode>(Kind::OBJECT, std::move(anyNonConst)));
        }
      }

      std::unique_ptr<ObjectFieldNodeBase> parseObjectField(bool isConst) {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *start = this->lexer->token;
        auto name = this->parseName();
        this->expectToken(TokenKind::COLON);
        return this->node<ObjectFieldNode>(start, std::make_unique<ObjectFieldNode>(Kind::OBJECT_FIELD, std::move(name), this->parseValueLiteral(isConst)));
      }

      std::vector<std::unique_ptr<ConstDirectiveNode>> parseConstDirectives() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto directives = this->parseDirectives(true);
        auto constDirectives = std::vector<std::unique_ptr<ConstDirectiveNode>>();
        for (auto &d : directives)
          constDirectives.push_back(std::make_unique<ConstDirectiveNode>(dynamic_cast<ConstDirectiveNode&>(*d)));
        return constDirectives;
      }

      std::unique_ptr<StringValueNode> parseDescription() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        if (this->peekDescription())
          return this->parseStringLiteral();
        return nullptr;
      }

      std::unique_ptr<SchemaDefinitionNode> parseSchemaDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *start = this->lexer->token;
        std::unique_ptr<StringValueNode> description = this->parseDescription();
        this->expectKeyword(L"schema");
        auto directives = this->parseConstDirectives();
        auto operationTypes = this->many<OperationTypeDefinitionNode>(TokenKind::BRACE_L, &Parser::parseOperationTypeDefinition, TokenKind::BRACE_R);
        return this->node<SchemaDefinitionNode>(start, std::make_unique<SchemaDefinitionNode>(Kind::SCHEMA_DEFINITION, std::move(description), std::move(directives), std::move(operationTypes)));
      }

      OperationTypeNode parseOperationType() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto operationToken = this->expectToken(TokenKind::NAME);
        if (operationToken->value.compare(L"query") == 0)
          return OperationTypeNode::QUERY;
        if (operationToken->value.compare(L"mutation") == 0)
          return OperationTypeNode::MUTATION;
        if (operationToken->value.compare(L"subscription") == 0)
          return OperationTypeNode::SUBSCIPTION;
        throw this->unexpected(operationToken);
      }

      std::unique_ptr<OperationTypeDefinitionNode> parseOperationTypeDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        Token *start = this->lexer->token;
        auto operation = this->parseOperationType();
        this->expectToken(TokenKind::COLON);
        auto type = this->parseNamedType();
        return this->node<OperationTypeDefinitionNode>(start, std::make_unique<OperationTypeDefinitionNode>(Kind::OPERATION_TYPE_DEFINITION, std::move(operation), std::move(type)));
      }

      std::unique_ptr<ScalarTypeDefinitioNode> parseScalarTypeDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        auto description = this->parseDescription();
        this->expectKeyword(L"scalar");
        auto name = this->parseName();
        auto directives = this->parseConstDirectives();
        return this->node<ScalarTypeDefinitioNode>(start, std::make_unique<ScalarTypeDefinitioNode>(Kind::SCALAR_TYPE_DEFINITION, std::move(description), std::move(name), std::move(directives)));
      }

      std::unique_ptr<ObjectTypeDefinitionNode> parseObjectTypeDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        auto description = this->parseDescription();
        this->expectKeyword(L"type");
        auto name = this->parseName();
        auto interfaces = this->parseImplementsInterfaces();
        auto directives = this->parseConstDirectives();
        auto fields = this->parseFieldsDefinition();
        return this->node<ObjectTypeDefinitionNode>(start, std::make_unique<ObjectTypeDefinitionNode>(Kind::OBJECT_TYPE_DEFINITION, std::move(description), std::move(name), std::move(interfaces), std::move(directives), std::move(fields)));
      }

      std::vector<std::unique_ptr<NamedTypeNode>> parseImplementsInterfaces() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->expectOptionalKeyword(L"implements") ? this->delimitedMany(TokenKind::AMP, &Parser::parseNamedType) : std::vector<std::unique_ptr<NamedTypeNode>>();
      }

      std::unique_ptr<InterfaceTypeDefinitionNode> parseInterfaceTypeDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        auto description = this->parseDescription();
        this->expectKeyword(L"interface");
        auto name = this->parseName();
        auto interfaces = this->parseImplementsInterfaces();
        auto directives = this->parseConstDirectives();
        auto fields = this->parseFieldsDefinition();
        return this->node<InterfaceTypeDefinitionNode>(start, std::make_unique<InterfaceTypeDefinitionNode>(Kind::INTERFACE_TYPE_DEFINITION, std::move(description), std::move(name), std::move(interfaces), std::move(directives), std::move(fields)));
      }

      std::vector<std::unique_ptr<FieldDefinitionNode>> parseFieldsDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        this->optionalMany<FieldDefinitionNode>(TokenKind::BRACE_L, &Parser::parseFieldDefinition, TokenKind::BRACE_R);
      };

      std::unique_ptr<FieldDefinitionNode> parseFieldDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        auto description = this->parseDescription();
        auto name = this->parseName();
        auto args = this->parseArgumentDefs();
        this->expectToken(TokenKind::COLON);
        auto type = this->parseTypeReference();
        auto directives = this->parseConstDirectives();
        return this->node<FieldDefinitionNode>(start, std::make_unique<FieldDefinitionNode>(Kind::FIELD_DEFINITION, std::move(description), std::move(name), std::move(args), std::move(type), std::move(directives)));
      }

      std::vector<std::unique_ptr<InputValueDefinitionNode>> parseArgumentDefs() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->optionalMany<InputValueDefinitionNode>(TokenKind::PAREN_L, &Parser::parseInputValueDef, TokenKind::PAREN_R);
      }

      std::unique_ptr<UnionTypeDefinitionNode> parseUnionTypeDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        auto description = this->parseDescription();
        this->expectKeyword(L"union");
        auto name = this->parseName();
        auto directives = this->parseConstDirectives();
        auto types = this->parseUnionMemberTypes();
        return this->node<UnionTypeDefinitionNode>(start, std::make_unique<UnionTypeDefinitionNode>(Kind::UNION_TYPE_DEFINITION, std::move(description), std::move(name), std::move(directives), std::move(types)));
      }

      std::vector<std::unique_ptr<NamedTypeNode>> parseUnionMemberTypes() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->expectOptionalToken(TokenKind::EQUALS) ? this->delimitedMany<NamedTypeNode>(TokenKind::PIPE, &Parser::parseNamedType) : std::vector<std::unique_ptr<NamedTypeNode>>();
      }

      std::unique_ptr<EnumTypeDefinitionNode> parseEnumTypeDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        auto description = this->parseDescription();
        this->expectKeyword(L"enum");
        auto name = this->parseName();
        auto directives = this->parseConstDirectives();
        auto values = this->parseEnumValuesDefinition();
        return this->node<EnumTypeDefinitionNode>(start, std::make_unique<EnumTypeDefinitionNode>(Kind::ENUM_TYPE_DEFINITION, std::move(description), std::move(name), std::move(directives), std::move(values)));
      }

      std::vector<std::unique_ptr<EnumValueDefinitionNode>> parseEnumValuesDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->optionalMany<EnumValueDefinitionNode>(TokenKind::BRACE_L, &Parser::parseEnumValueDefinition, TokenKind::BRACE_R);
      }

      std::unique_ptr<EnumValueDefinitionNode> parseEnumValueDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        auto description = this->parseDescription();
        auto name = this->parseEnumValueName();
        auto directives = this->parseConstDirectives();
        return this->node<EnumValueDefinitionNode>(start, std::make_unique<EnumValueDefinitionNode>(Kind::ENUM_VALUE_DEFINITION, std::move(description), std::move(name), std::move(directives)));
      }

      std::unique_ptr<NameNode> parseEnumValueName() {
        if (this->lexer->token->value.compare(L"true") == 0 || this->lexer->token->value.compare(L"false") == 0 || this->lexer->token->value.compare(L"null") == 0)
          throw GraphQLSyntaxError(this->lexer->source, this->lexer->token->start, getTokenDesc(this->lexer->token) + " is reserved and cannot be used for an enum value.");
      }

      std::unique_ptr<InputObjectTypeDefinitionNode> parseInputObjectTypeDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        auto description = this->parseDescription();
        this->expectKeyword(L"input");
        auto name = this->parseName();
        auto directives = this->parseConstDirectives();
        auto fields = this->parseInputFieldsDefinition();
        return this->node<InputObjectTypeDefinitionNode>(start, std::make_unique<InputObjectTypeDefinitionNode>(Kind::INPUT_OBJECT_TYPE_DEFINITION, std::move(description), std::move(name), std::move(directives), std::move(fields)));
      }

      std::vector<std::unique_ptr<InputValueDefinitionNode>> parseInputFieldsDefinition() {
        return this->optionalMany<InputValueDefinitionNode>(TokenKind::BRACE_L, &Parser::parseInputValueDef, TokenKind::BRACE_R);
      }

      std::unique_ptr<InputValueDefinitionNode> parseInputValueDef() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        auto description = this->parseDescription();
        auto name = this->parseName();
        this->expectToken(TokenKind::COLON);
        auto type = this->parseTypeReference();
        std::unique_ptr<ConstValueNode> defaultValue;
        if (this->expectOptionalToken(TokenKind::EQUALS))
          defaultValue = this->parseConstValueLiteral();
        auto directives = this->parseConstDirectives();
        return this->node<InputValueDefinitionNode>(start, std::make_unique<InputValueDefinitionNode>(Kind::INPUT_VALUE_DEFINITION, std::move(description), std::move(name), std::move(type), std::move(defaultValue), std::move(directives)));
      }

      std::unique_ptr<DirectiveDefinitionNode> parseDirectiveDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        auto description = this->parseDescription();
        this->expectKeyword(L"directive");
        this->expectToken(TokenKind::AT);
        auto name = this->parseName();
        auto args = this->parseArgumentDefs();
        auto repeatable = this->expectOptionalKeyword(L"repeatable");
        this->expectKeyword(L"on");
        auto locations = this->parseDirectiveLocations();
        return this->node<DirectiveDefinitionNode>(start, std::make_unique<DirectiveDefinitionNode>(Kind::DIRECTIVE_DEFINITION, std::move(description), std::move(name), std::move(args), repeatable, std::move(locations)));
      }

      std::vector<std::unique_ptr<NameNode>> parseDirectiveLocations() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        return this->delimitedMany<NameNode>(TokenKind::PIPE, &Parser::parseDirectiveLocation);
      }

      std::unique_ptr<NameNode> parseDirectiveLocation() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto start = this->lexer->token;
        auto name = this->parseName();
        if (directiveLocation.find(name->value) != directiveLocation.end())
          return name;
        throw this->unexpected(start);
      }

      std::unique_ptr<FragmentDefinitionNode> parseFragmentDefinition() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif

        auto start = this->lexer->token;
        this->expectKeyword(L"fragment");
        if (this->options != nullptr && this->options->allowLegacyFragmentVariables)
          return this->node<FragmentDefinitionNode>(start, std::make_unique<FragmentDefinitionNode>(Kind::FRAGMENT_DEFINITION, this->parseFragmentName(), this->parseVariableDefinitions(), (this->expectKeyword(L"on"), this->parseNamedType()), this->parseDirectives(false), this->parseSelectionSet()));
        return this->node<FragmentDefinitionNode>(start, std::make_unique<FragmentDefinitionNode>(Kind::FRAGMENT_DEFINITION, this->parseFragmentName(), (this->expectKeyword(L"on"), this->parseNamedType()), this->parseDirectives(false), this->parseSelectionSet()));
      }

      std::unique_ptr<TypeSystemExtensionNode> parseTypeSystemExtension() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif

        auto keywordToken = this->lexer->lookahead();

        if (keywordToken->kind == TokenKind::NAME) {
          if (keywordToken->value.compare(L"schema") == 0)
            return this->parseSchemaExtension();
          if (keywordToken->value.compare(L"scalar") == 0)
            return this->parseScalarTypeExtension();
          if (keywordToken->value.compare(L"type") == 0)
            return this->parseObjectTypeExtension();
          if (keywordToken->value.compare(L"interface") == 0)
            return this->parseInterfaceTypeExtension();
          if (keywordToken->value.compare(L"union") == 0)
            return this->parseUnionTypeExtension();
          if (keywordToken->value.compare(L"enum") == 0)
            return this->parseEnumTypeExtension();
          if (keywordToken->value.compare(L"input") == 0)
            return this->parseInputObjectTypeExtension();
        }

        throw this->unexpected(keywordToken);
      }

      std::unique_ptr<SchemaExtensionNode> parseSchemaExtension() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif

      }
      std::unique_ptr<ScalarTypeExtensionNode> parseScalarTypeExtension() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif

      }

      std::unique_ptr<ObjectTypeExtensionNode> parseObjectTypeExtension() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif

      }

      std::unique_ptr<InterfaceTypeExtensionNode> parseInterfaceTypeExtension() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif

      }

      std::unique_ptr<UnionTypeExtensionNode> parseUnionTypeExtension() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif

      }

      std::unique_ptr<EnumTypeExtensionNode> parseEnumTypeExtension() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif

      }

      std::unique_ptr<InputObjectTypeExtensionNode> parseInputObjectTypeExtension() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif

      }
  };

  std::unique_ptr<DocumentNode> parse(Source *source, ParseOptions *options = nullptr) {
#ifdef DEBUG
    std::cout << __func__ << std::endl;
#endif
    auto parser = new Parser(source, options);
    return parser->parseDocument();
  }
}
