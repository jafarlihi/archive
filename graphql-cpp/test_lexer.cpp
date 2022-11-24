#include "graphql-cpp.hpp"

#include <cassert>
#include <exception>
#include <iostream>

#include <fmt/core.h>
#include <fmt/xchar.h>

using namespace graphql;

Token *lexOne(std::wstring str) {
  Lexer *lexer = new Lexer(new Source(str));
  return lexer->advance();
}

Token *lexSecond(std::wstring str) {
  Lexer *lexer = new Lexer(new Source(str));
  lexer->advance();
  return lexer->advance();
}

bool tokenContains(Token *token, TokenKind kind, int start, int end, std::wstring value) {
  if (token->kind == kind && token->start == start && token->end == end && token->value.compare(value) == 0) return true;
  std::wcerr << static_cast<int>(token->kind) << " " << token->start << " " << token->end << " " << token->value << std::endl;
  std::wcerr << token->value;
  return false;
}

bool tokenContains2(Token *token, TokenKind kind, int start, int end, int line, int column, std::wstring value) {
  if (token->kind == kind && token->start == start && token->end == end && token->line == line && token->column == column && token->value.compare(value) == 0) return true;
  std::wcerr << static_cast<int>(token->kind) << " " << token->start << " " << token->end << " " << token->line << " " << token->column << " " << token->value << std::endl;
  return false;
}



int main(int argc, char *argv[]) {
  try {
    Lexer *lexer = new Lexer(new Source(L"\uFEFF foo"));
  } catch (const std::exception &e) {
    std::cerr << "HERE" << std::endl;
  }
  try {
    assert(tokenContains(lexOne(L"\uFEFF foo"), TokenKind::NAME, 2, 5, L"foo"));
  } catch (const std::exception &e) {
    std::cerr << e.what();
  }
  assert(tokenContains2(lexOne(L"foo"), TokenKind::NAME, 0, 3, 1, 1, L"foo"));

  assert(tokenContains2(lexOne(L"\nfoo"), TokenKind::NAME, 1, 4, 2, 1, L"foo"));

  assert(tokenContains2(lexOne(L"\rfoo"), TokenKind::NAME, 1, 4, 2, 1, L"foo"));

  assert(tokenContains2(lexOne(L"\r\nfoo"), TokenKind::NAME, 2, 5, 2, 1, L"foo"));

  assert(tokenContains2(lexOne(L"\n\rfoo"), TokenKind::NAME, 2, 5, 3, 1, L"foo"));

  assert(tokenContains2(lexOne(L"\r\r\n\nfoo"), TokenKind::NAME, 4, 7, 4, 1, L"foo"));


  assert(tokenContains2(lexOne(L"\n\n\r\rfoo"), TokenKind::NAME, 4, 7, 5, 1, L"foo"));


  assert(tokenContains2(lexOne(L"\n \r\n \r  foo\n"), TokenKind::NAME, 8, 11, 4, 3, L"foo"));

  assert(tokenContains(lexOne(L"\n"
          L"\n"
          L"    foo"
          L"\n"
          L"\n"), TokenKind::NAME, 6, 9, L"foo"));

  assert(tokenContains(lexOne(L"\t\tfoo\t\t"), TokenKind::NAME, 2, 5, L"foo"));

  assert(tokenContains(lexOne(L"\n"
          L"    #comment\n"
          L"    foo#comment\n"
          L""), TokenKind::NAME, 18, 21, L"foo"));

  assert(tokenContains(lexOne(L",,,foo,,,"), TokenKind::NAME, 3, 6, L"foo"));

  std::string err;
  try {
    lexOne(L"\n\n ~\n\n");
  } catch (const GraphQLError &e) {
    err = e.message;
  }
  assert(err.compare("Syntax Error: Unexpected character: ?.") == 0); // TODO FIX

  try {
    lexOne(L"\n\n     ~\n\n");
  } catch (const GraphQLError &e) {
    err = e.message;
  }
  assert(err.compare("Syntax Error: Unexpected character: ?.") == 0);

  try {
    Source *source = new Source(L"~", "foo.js", SourceLocation(1, 1));
    (new Lexer(source))->advance();
  } catch (const GraphQLError &e) {
    err = e.message;
  }

  assert(err.compare("Syntax Error: Unexpected character: ?.") == 0);
  assert(tokenContains(lexOne(L"\"simple\""), TokenKind::STRING, 0, 8, L"simple"));
  assert(tokenContains(lexOne(L"\" white space \""), TokenKind::STRING, 0, 15, L" white space "));
  assert(tokenContains(lexOne(L"\"quote \\\"\""), TokenKind::STRING, 0, 10, L"quote \""));
  assert(tokenContains(lexOne(L"\"escaped \\\\n\\\\r\\\\b\\\\t\\\\f\""), TokenKind::STRING, 0, 25, L"escaped \\n\\r\\b\\t\\f"));
  assert(tokenContains(lexOne(L"\"slashes \\\\ \\/\""), TokenKind::STRING, 0, 15, L"slashes \\ /"));

  assert(tokenContains(lexOne(L"\"unescaped unicode outside BMP \u1f600\""), TokenKind::STRING, 0, 34, L"unescaped unicode outside BMP \u1f600"));

  assert(tokenContains(lexOne(L"\"unescaped unicode outside BMP \\\\u10ffff\""), TokenKind::STRING, 0, 41, L"unescaped unicode outside BMP \\u10ffff"));

  assert(tokenContains(lexOne(L"\"unicode \\\\u1234\\\\u5678\\\\u90AB\\\\uCDEF\""), TokenKind::STRING, 0, 38, L"unicode \\u1234\\u5678\\u90AB\\uCDEF"));

  assert(tokenContains(lexOne(L"\"unicode \\\\u{1234}\\\\u{5678}\\\\u{90AB}\\\\u{CDEF}\""), TokenKind::STRING, 0, 46, L"unicode \\u{1234}\\u{5678}\\u{90AB}\\u{CDEF}"));

  assert(tokenContains(lexOne(L"\"string with unicode escape outside BMP \\\\u{1F600}\""), TokenKind::STRING, 0, 51, L"string with unicode escape outside BMP \\u{1F600}"));


  assert(tokenContains(lexOne(L"\"string with minimal unicode escape \\\\u{0}\""), TokenKind::STRING, 0, 43, L"string with minimal unicode escape \\u{0}"));


  assert(tokenContains(lexOne(L"\"string with maximal unicode escape \\\\u{10FFFF}\""), TokenKind::STRING, 0, 48, L"string with maximal unicode escape \\u{10FFFF}"));



  assert(tokenContains(lexOne(L"\"string with maximal minimal unicode escape \\\\u{00000000}\""), TokenKind::STRING, 0, 58, L"string with maximal minimal unicode escape \\u{00000000}"));


  //Token *token = lexOne(L"\"string with unicode surrogate pair escape \\uD83D\\uDE00\"");
  //assert(tokenContains(token, TokenKind::STRING, 0, 56, L"string with unicode surrogate pair escape \u1f600")); // TODO FIX


  //assert(tokenContains(lexOne(L"\"string with unicode surrogate pair escape \\uD83D\\uDE00\""), TokenKind::STRING, 0, 56, L"string with unicode surrogate pair escape \u1f600")); // TODO FIX


  //assert(tokenContains(lexOne(L"\"string with unicode surrogate pair escape \\uD83D\\uDE00\""), TokenKind::STRING, 0, 56, L"string with unicode surrogate pair escape \u1f600")); // TODO FIX


  std::string message;


  try {
    lexSecond(L"\"");
  } catch(const GraphQLSyntaxError  e) {
    message = e.message;
  }
  assert(message.compare("Syntax Error: Unterminated string.") == 0);


  try {
    lexSecond(L"\"\"\"");
  } catch(const GraphQLSyntaxError  e) {
    message = e.message;
  }
  assert(message.compare("Syntax Error: Unterminated string.") == 0);


  try {
    lexSecond(L"\"\"\"\"");
  } catch(const GraphQLSyntaxError  e) {
    message = e.message;
  }
  assert(message.compare("Syntax Error: Unterminated string.") == 0);


  try {
    lexSecond(L"\"no end quote");
  } catch(const GraphQLSyntaxError  e) {
    message = e.message;
  }
  assert(message.compare("Syntax Error: Unterminated string.") == 0);


  try {
    lexSecond(L"'single quotes'");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Unexpected single quote character ('), did you mean to use a double quote") == 0);



  try {
    lexSecond(L"\"bad surrogate \\uDEAD\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid") == 0);



  try {
    lexSecond(L"\"bad high surrogate pair \\uDEAD\\uDEAD\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid") == 0);



  try {
    lexSecond(L"\"bad low surrogate pair \\uD800\\uD800\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid") == 0);



  try {
    lexSecond(L"\"multi\nline\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.compare("Syntax Error: Unterminated string.") == 0);



  try {
    lexSecond(L"\"multi\rline\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.compare("Syntax Error: Unterminated string.") == 0);



  try {
    lexSecond(L"\"bad \\z esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid character escape sequence") == 0);



  try {
    lexSecond(L"\"bad \\x esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid character escape sequence") == 0);



  try {
    lexSecond(L"\"bad \\u1 esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad \\u0XX1 esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad \\uXXXX esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad \\uFXXX esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad \\uXXXF esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad \\u{} esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad \\u{FXXX} esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad \\u{FFFF esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);
  try {
    lexSecond(L"\"bad \\u{FFFF\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);

  try {
    lexSecond(L"\"too high \\u{110000} esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"way too high \\u{12345678} esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"too long \\u{000000000} esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad surrogate \\uDEAD esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad surrogate \\u{DEAD} esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);
  try {
    lexSecond(L"\"cannot use braces for surrogate pair \\u{D83D}\\u{DE00} esc.");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad high surrogate pair \\uDEAD\\uDEAD esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad low surrogate pair \\uD800\\uD800 esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);
  try {
    lexSecond(L"\"cannot escape half a pair \\uD83D\\\\uDE00 esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid") == 0);
  try {
    lexSecond(L"\"cannot escape half a pair \\uD83D\\uDE00 esc\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);



  try {
    lexSecond(L"\"bad \\uD83D\\not an escape\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Invalid Unicode escape sequence") == 0);


   assert(tokenContains2(lexOne(L"\"\"\"\"\"\""), TokenKind::BLOCK_STRING,0,6,1,1,L""));

    assert(tokenContains2(lexOne(L"\"\"\"simple\"\"\""), TokenKind::BLOCK_STRING,0,12,1,1,L"simple"));

    assert(tokenContains2(lexOne(L"\"\"\" white space \"\"\""), TokenKind::BLOCK_STRING,0,19,1,1,L" white space "));

    assert(tokenContains2(lexOne(L"\"\"\"contains \" quote\"\"\""), TokenKind::BLOCK_STRING,0,22,1,1,L"contains \" quote"));

    assert(tokenContains2(lexOne(L"\"\"\"contains \\\"\"\" triple quote\"\"\""), TokenKind::BLOCK_STRING,0,32,1,1,L"contains \"\"\" triple quote"));

    assert(tokenContains2(lexOne(L"\"\"\"multi\nline\"\"\""), TokenKind::BLOCK_STRING,0,16,1,1,L"multi\nline"));

    assert(tokenContains2(lexOne(L"\"\"\"multi\rline\r\nnormalized\"\"\""), TokenKind::BLOCK_STRING,0,28,1,1,L"multi\nline\nnormalized"));

    assert(tokenContains2(lexOne(L"\"\"\"unescaped \\n\\r\\b\\t\\f\\u1234\"\"\""), TokenKind::BLOCK_STRING,0,32,1,1,L"unescaped \\n\\r\\b\\t\\f\\u1234"));

    assert(tokenContains2(lexOne(L"\"\"\"unescaped unicode outside BMP \\u{1f600}\"\"\""), TokenKind::BLOCK_STRING,0,45,1,1,L"unescaped unicode outside BMP \\u{1f600}"));

    assert(tokenContains2(lexOne(L"\"\"\"slashes \\\\ \\/\"\"\""), TokenKind::BLOCK_STRING,0,19,1,1,L"slashes \\\\ \\/"));

    //assert(tokenContains2(lexOne(L"\"\"\"\n\n        spans\n          multiple\n              lines\n\n\"\"\""), TokenKind::BLOCK_STRING,0,68,1,1,L"spans\n  multiple\n    lines"));

assert(tokenContains2(lexSecond(L"\"\"\"\n\n        spans\n          multiple\n              lines\n\n\"\"\" second_token"), TokenKind::NAME,63,75,7,5,L"second_token"));

assert(tokenContains2(lexSecond(L"\"\"\" \nspans \r\nmultiple \n\rlines\n\n\"\"\"\n second_token"), TokenKind::NAME,36,48,8,2,L"second_token"));

  try {
    lexOne(L"\"\"\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Unterminated string.") == 0);

  try {
    lexOne(L"\"\"\"no end quote");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error: Unterminated string.") == 0);

  try {
    lexOne(L"\"\"\"contains invalid surrogate \\uDEAD\"\"\"");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  //assert(message.find("Syntax Error: Invalid") == 0);


 assert(tokenContains(lexOne(L"4"), TokenKind::INT, 0, 1, L"4"));
   

    assert(tokenContains(lexOne(L"4.123"), TokenKind::FLOAT, 0, 5, L"4.123"));
   

    assert(tokenContains(lexOne(L"-4"), TokenKind::INT, 0, 2, L"-4"));
   

    assert(tokenContains(lexOne(L"9"), TokenKind::INT, 0, 1, L"9"));
   

    assert(tokenContains(lexOne(L"0"), TokenKind::INT, 0, 1, L"0"));
   

    assert(tokenContains(lexOne(L"-4.123"), TokenKind::FLOAT, 0, 6, L"-4.123"));
   

    assert(tokenContains(lexOne(L"0.123"), TokenKind::FLOAT, 0, 5, L"0.123"));
   

    assert(tokenContains(lexOne(L"123e4"), TokenKind::FLOAT, 0, 5, L"123e4"));
   

    assert(tokenContains(lexOne(L"123E4"), TokenKind::FLOAT, 0, 5, L"123E4"));
   

    assert(tokenContains(lexOne(L"123e-4"), TokenKind::FLOAT, 0, 6, L"123e-4"));
   

    assert(tokenContains(lexOne(L"123e+4"), TokenKind::FLOAT, 0, 6, L"123e+4"));
   

    assert(tokenContains(lexOne(L"-1.123e4"), TokenKind::FLOAT, 0, 8, L"-1.123e4"));
   

    assert(tokenContains(lexOne(L"-1.123E4"), TokenKind::FLOAT, 0, 8, L"-1.123E4"));
   

    assert(tokenContains(lexOne(L"-1.123e-4"), TokenKind::FLOAT, 0, 9, L"-1.123e-4"));
   

    assert(tokenContains(lexOne(L"-1.123e+4"), TokenKind::FLOAT, 0, 9, L"-1.123e+4"));
   

    assert(tokenContains(lexOne(L"-1.123e4567"), TokenKind::FLOAT, 0, 11, L"-1.123e4567"));
   
 

try{
  lexOne(L"00");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"01");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"01.23");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"+1");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"1.");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"1e");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"1E");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"1.e1");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L".123");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"1.A");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"-A");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"1.0e");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"1.0eA");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"1.0e\"");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"1.2e3e");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"1.2e3.4");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"1.23.4");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);




  try{
    lexOne(L"0xF1");
  } catch (const GraphQLSyntaxError &e) {
    message = e.message;
  }
  assert(message.find("Syntax Error") == 0);


try{
  lexOne(L"0b10");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);


try{
  lexOne(L"123abc");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);


try{
  lexOne(L"1_234");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);


try{
  lexOne(L"1\u00DF");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);


try{
  lexOne(L"1.23f");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);


try{
  lexOne(L"1.234_5");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



    assert(tokenContains(lexOne(L"!"), TokenKind::BANG,0,1,L""));
    

    assert(tokenContains(lexOne(L"?"), TokenKind::QUESTION_MARK,0,1,L""));
    

    assert(tokenContains(lexOne(L"$"), TokenKind::DOLLAR,0,1,L""));
    

    assert(tokenContains(lexOne(L"(L"), TokenKind::PAREN_L,0,1,L""));
    

    assert(tokenContains(lexOne(L")"), TokenKind::PAREN_R,0,1,L""));
    

    assert(tokenContains(lexOne(L"..."), TokenKind::SPREAD,0,3,L""));
    

    assert(tokenContains(lexOne(L":"), TokenKind::COLON,0,1,L""));
    

    assert(tokenContains(lexOne(L"="), TokenKind::EQUALS,0,1,L""));
    

    assert(tokenContains(lexOne(L"@"), TokenKind::AT,0,1,L""));
    

    assert(tokenContains(lexOne(L"["), TokenKind::BRACKET_L,0,1,L""));
    

    assert(tokenContains(lexOne(L"]"), TokenKind::BRACKET_R,0,1,L""));
    

    assert(tokenContains(lexOne(L"{"), TokenKind::BRACE_L,0,1,L""));
    

    assert(tokenContains(lexOne(L"|"), TokenKind::PIPE,0,1,L""));
    

    assert(tokenContains(lexOne(L"}"), TokenKind::BRACE_R,0,1,L""));
    

try{
  lexOne(L"..");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"~");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"\\x00");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"\\b");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"\\u00AA");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"\\u0AAA");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"\\u203B");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"\\u{1f600}");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"\\uD83D\\uDE00");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"\\uD800\\uDC00");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"\\uDBFF\\uDFFF");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);



try{
  lexOne(L"\\uDEAD");
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);


Source *source = new Source(L"a-b");
Lexer *lexer = new Lexer(source);
Token *firstToken = lexer->advance();
assert(tokenContains(firstToken, TokenKind::NAME, 0, 1, L"a"));

try {
  lexer->advance();
} catch (const GraphQLSyntaxError &e) {
  message = e.message;
}
assert(message.find("Syntax Error") == 0);

source = new Source(L"\n{\n#comment\nfield\n}\n");
lexer = new Lexer(source);
Token *startToken = lexer->token;
Token *endToken;
do {
  endToken = lexer->advance();
  assert(endToken->kind != TokenKind::COMMENT);
} while (endToken->kind != TokenKind::EOF);

assert(startToken->prev == nullptr);
assert(endToken->next == nullptr);

  std::vector<Token *> vec = std::vector<Token *>();
  for (Token *tok = startToken; tok; tok = tok->next) {
    if (vec.size())
      assert(tok->prev == vec[vec.size() - 1]);
    vec.push_back(tok);
  }

  assert(vec[0]->kind == TokenKind::SOF);

  assert(vec[1]->kind == TokenKind::BRACE_L);

  assert(vec[2]->kind == TokenKind::COMMENT);

  assert(vec[3]->kind == TokenKind::NAME);

  assert(vec[4]->kind == TokenKind::BRACE_R);

  assert(vec[5]->kind == TokenKind::EOF);

// TODO more stuff

  return 0;
}
