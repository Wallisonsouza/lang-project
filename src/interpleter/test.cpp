
// #include "core/node/Type.hpp"
// #include "parser/node/literal_nodes.hpp"
// #include "parser/node/operator_nodes.hpp"
// #include <string>
// #include <variant>

// using Value = std::variant<double, std::string, std::u32string>;

// Value evaluete_literals(core::node::ExpressionNode *expr) {
//   using namespace core::node;

//   switch (expr->kind) {
//   case NodeKind::NumberLiteral:
//     return static_cast<node::NumberLiteralNode *>(expr)->value;

//   case NodeKind::StringLiteral:
//     return static_cast<node::StringLiteralNode *>(expr)->value;

//   default:
//     throw std::runtime_error("eval: nó não suportado");
//   }
// }

// Value evaluete_binary_expression(node::BinaryExpressionNode *expr) {

//   using namespace core::node;

//   double left = std::get<double>(eval(bin->left));
//   double right = std::get<double>(eval(bin->right));

//   switch (bin->op) {
//   case BinaryOp::Add:
//     return left + right;
//   case BinaryOp::Subtract:
//     return left - right;
//   case BinaryOp::Multiply:
//     return left * right;
//   case BinaryOp::Divide:
//     return left / right;
//   default:
//     throw std::runtime_error("Operador desconhecido");
//   }
// }