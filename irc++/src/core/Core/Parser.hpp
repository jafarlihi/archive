#pragma once

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace Parser {
using Tags = std::map<std::string, std::string>;
using Tag = std::pair<std::string, std::string>;
struct Message {
  Tags tags;
  std::string prefix;
  std::string command;
  std::vector<std::string> args;
  uint32_t flags{};
};

std::optional<Message> tokenize(std::string const &data);
} // namespace Parser
