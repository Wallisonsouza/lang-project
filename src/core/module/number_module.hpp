#include "core/module/Scope.hpp"
#include "parser/node/literal_nodes.hpp"

inline void import_number_module(core::Scope &scope) {

  auto *type_node = scope.arena.create<core::node::TypeDeclarationNode>(
      U"Number", std::vector<std::u32string>{});

  scope.declare(U"Number", core::SymbolKind::Type, type_node,
                core::Visibility::Public, true);

  auto *number_type = scope.find(U"Number");

  scope.operators_table.register_operation(
      core::node::BinaryOp::Add,
      static_cast<core::node::TypeNode *>(number_type->declaration),
      static_cast<core::node::TypeNode *>(number_type->declaration),

      [&scope](core::node::ExpressionNode *lhs, core::node::ExpressionNode *rhs)
          -> core::node::ExpressionNode * {
        auto *l = static_cast<node::NumberLiteralNode *>(lhs);
        auto *r = static_cast<node::NumberLiteralNode *>(rhs);

        return scope.arena.create<node::NumberLiteralNode>(l->value + r->value);
      });
}