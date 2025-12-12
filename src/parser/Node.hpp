// #pragma once
// #include <memory>
// #include <string>

// namespace interpreter::parser {

// enum class NodeKind {
//   Expression,
//   Statement,
//   NumberLiteral,
//   Identifier,
//   BinaryExpression,
//   VariableDeclaration,
//   StringLiteral
// };

// // Base
// struct Node {
//   const NodeKind kind;
//   explicit Node(NodeKind kind) : kind(kind) {}
//   virtual ~Node() = default;
// };

// struct ExpressionNode : Node {
//   explicit ExpressionNode(NodeKind kind) : Node(kind) {}
// };

// struct Statement : Node {
//   explicit Statement(NodeKind kind) : Node(kind) {}
// };

// // Literais
// struct NumberLiteralNode : ExpressionNode {
//   double value;
//   explicit NumberLiteralNode(double v)
//       : ExpressionNode(NodeKind::NumberLiteral), value(v) {}
// };

// struct StringLiteralNode : ExpressionNode {
//   std::u32string value;
//   explicit StringLiteralNode(std::u32string v)
//       : ExpressionNode(NodeKind::StringLiteral), value(std::move(v)) {}
// };

// struct IdentifierNode : ExpressionNode {
//   std::u32string name;
//   explicit IdentifierNode(std::u32string n)
//       : ExpressionNode(NodeKind::Identifier), name(std::move(n)) {}
// };

// struct BinaryExpression : ExpressionNode {
//   std::shared_ptr<ExpressionNode> left;
//   std::u32string op;
//   std::shared_ptr<ExpressionNode> right;

//   BinaryExpression(std::shared_ptr<ExpressionNode> l, std::u32string o,
//                    std::shared_ptr<ExpressionNode> r)
//       : ExpressionNode(NodeKind::BinaryExpression), left(std::move(l)),
//         op(std::move(o)), right(std::move(r)) {}
// };

// struct VariableDeclaration : Statement {
//   std::u32string name;
//   std::u32string type;
//   std::shared_ptr<ExpressionNode> value;
//   bool reactive;

//   VariableDeclaration(std::u32string n, std::u32string t,
//                       std::shared_ptr<ExpressionNode> val, bool r = false)
//       : Statement(NodeKind::VariableDeclaration), name(std::move(n)),
//         type(std::move(t)), value(std::move(val)), reactive(r) {}
// };

// struct IfStatementNode {};

// } // namespace interpreter::parser
