#include "graphql-cpp.hpp"

#include <cassert>
#include <exception>
#include <iostream>

#include <fmt/core.h>
#include <fmt/xchar.h>
#include <memory>
#include <typeinfo>

using namespace graphql;

auto unwrap(std::exception_ptr ptr) -> const GraphQLError&
{
    try {
        std::rethrow_exception(ptr);
    }
    catch (GraphQLError const& e) {
        return e;
    }
}

int main(int argc, char *argv[]) {
  std::exception_ptr eptr;
  try {
    parse(new Source(L"{"));
  } catch (const GraphQLError &e) {
    eptr = std::current_exception();
  }
  const auto& exp = unwrap(eptr);
  assert(exp.message.find("Syntax Error: Expected Name, found <EOF>") == 0);

  try {
  parse(new Source(L"{ field(complex: { a: { b: [ $var ] } }) }"));
  } catch (const GraphQLError &e) {
    std::cerr << e.message << std::endl;
    assert(false);
  } catch (const std::bad_cast &e) {
    std::cerr << e.what() << std::endl;
  }

  std::unique_ptr<DocumentNode> result = nullptr;
  try {
  result = parse(new Source(L"{ node(id: 4) { id, name } }"));
  } catch (const GraphQLError &e) {
    std::cerr << e.message << std::endl;
  }
  assert(result->kind == Kind::DOCUMENT);
  std::cout << result->definitions.size() << std::endl;
  std::cout << to_underlying(result->definitions[0]->kind) << std::endl;
  assert(result->definitions[0]->kind == Kind::OPERATION_DEFINITION);
  assert(result->definitions[0]->loc->start == 0);
  assert(result->definitions[0]->loc->end == 28);
  OperationDefinitionNode *node = dynamic_cast<OperationDefinitionNode *>(result->definitions[0].get());
  assert(node->selectionSet->kind == Kind::SELECTION_SET);
  FieldNode *node2 = dynamic_cast<FieldNode *>(node->selectionSet->selections[0].get());
  assert(node2->name->value.compare(L"node") == 0);
  return 0;
}
