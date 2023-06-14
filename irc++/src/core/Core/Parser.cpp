#include "Parser.hpp"

#include <iomanip>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/phoenix.hpp>
#include <boost/spirit/home/x3.hpp>

BOOST_FUSION_ADAPT_STRUCT(Parser::Message, tags, prefix, command, args);

namespace Parser {
enum MSG_FLAGS : uint32_t {
  MSG_TRAILING_ARG = (1 << 0),
  MSG_REPEAT_1ST = (1 << 1),
  MSG_NO_PREFIX = (1 << 2),
};

std::optional<Message> tokenize(std::string const &data) {
  namespace x3 = boost::spirit::x3;
  namespace ascii = boost::spirit::x3::ascii;
  using ascii::char_;
  using x3::double_;
  using x3::int_;
  using x3::lexeme;
  using x3::lit;
  using x3::omit;
  using x3::rule;

  Message msg;
  msg.flags = 0;
  static auto on_trailing_arg = [&](auto &) { msg.flags |= MSG_TRAILING_ARG; };

  static auto const token = lexeme[+(char_ - ' ' - ':')];
  static auto const tagname = rule<struct tagname_, std::string>{"tagname"} =
      lexeme[+~char_(" :;=")];
  static auto const tagvalue = tagname;
  static auto const prefix = omit[':'] >> token;
  static auto const trail = (omit[':'] >> lexeme[*char_])[on_trailing_arg];
  static auto const tag = rule<struct tags_, Tag>{"tag"} =
      tagname >> -('=' >> tagvalue);
  static auto const tags = rule<struct tags_, Tags>{"tags"} =
      omit['@'] >> tag % ';';
  static auto const line =
      -tags >> -prefix >> token >> ((+token > -trail) | trail);

  auto iter = data.begin();
  auto const end = data.end();
  auto result = x3::phrase_parse(iter, end, line, ascii::space, msg);
  if (result && iter == end) {
    return msg;
  }
  return std::nullopt;
}
} // namespace Parser
