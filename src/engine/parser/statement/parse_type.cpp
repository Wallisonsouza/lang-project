#include "engine/parser/parser.hpp"

core::node::TypeNode *Parser::parse_type() {

  auto identifier = parse_identifier_name();

  if (!identifier)
    return nullptr;

  std::vector<core::node::TypeNode *> generic_args;
  return unit.ast.create_node<core::node::TypeNode>(identifier, generic_args);
}
