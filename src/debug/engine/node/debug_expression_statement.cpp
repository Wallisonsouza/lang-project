#include "ast_debug.hpp"
#include "core/node/Type.hpp"

void ASTDebug::debug_expression_statement(const core::node::ExpressionStatementNode *node) {

  out << "ExpressionStatement\n";

  debug_node(node->expr, true);
}
