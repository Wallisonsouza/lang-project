#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "debug/engine/node/DebugNode.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "utils/Utf8.hpp"
#include <string>

inline void debug_number_literal(const parser::node::NumberLiteralNode *node,
                                 const std::string &prefix, bool isLast) {
  debug::node::print_prefix(prefix, isLast);
  debug::Console::log(debug::Color::BrightYellow,
                      "NumberLiteral: ", node->value);
}

inline void debug_string_literal(const parser::node::StringLiteralNode *node,
                                 const std::string &prefix, bool isLast) {
  debug::node::print_prefix(prefix, isLast);
  debug::Console::log(debug::Color::Orange, "StringLiteral: \"",
                      utils::Utf::utf32to8(node->value), "\"");
}

inline void debug_bool_literal(const parser::node::BoolLiteralNode *node,
                               const std::string &prefix, bool isLast) {
  debug::node::print_prefix(prefix, isLast);
  debug::Console::log(debug::Color::Cyan,
                      "BoolLiteral: ", node->value ? "true" : "false");
}

inline void debug_char_literal(const parser::node::CharLiteralNode *node,
                               const std::string &prefix, bool isLast) {
  debug::node::print_prefix(prefix, isLast);

  std::string out;
  utils::Utf::encode(node->value, out);

  debug::Console::log(debug::Color::Orange, "CharLiteral: '", out, "'");
}

inline void debug_null_literal(const parser::node::NullLiteralNode *node,
                               const std::string &prefix, bool isLast) {
  debug::node::print_prefix(prefix, isLast);
  debug::Console::log(debug::Color::BrightBlack, "NullLiteral");
}

inline void debug_identifier(const parser::node::IdentifierNode *node,
                             const std::string &prefix, bool isLast) {
  debug::node::print_prefix(prefix, isLast);
  debug::Console::log(debug::Color::Purple,
                      "Identifier: ", utils::Utf::utf32to8(node->name));
}