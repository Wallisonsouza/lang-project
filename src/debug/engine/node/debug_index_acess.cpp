#include "ast_debug.hpp"
#include "engine/parser/node/statement_nodes.hpp"

void ASTDebug::debug_index_acess(const parser::node::IndexAccessNode *node) {

  out << "IndexAcess\n";

  debug_labeled("Base", node->base, false);
  debug_labeled("Index", node->index, true);
}
