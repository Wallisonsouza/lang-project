#include "parse_expression.hpp"
#include "engine/parser/expression/parse_binary_expression.hpp"

namespace parser::expression {

core::node::ExpressionNode *parse_expression(CompilationUnit &unit, core::token::TokenStream &stream) { return parse_binary_expression(unit, stream, 0); }

} // namespace parser::expression
