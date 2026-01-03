#pragma once

namespace core::node {

enum class NodeKind {
  // === Base ===
  Unknown,

  NumberLiteral,
  StringLiteral,
  BoolLiteral,
  CharLiteral,
  NullLiteral,
  Identifier,
  PathExpr,

  // === Statements ===

  MemberAccess,
  IndexAccess,
  Block,
  IfStatement,
  WhileStatement,
  ForStatement,
  ReturnStatement,
  ExpressionStatement,
  Import,

  // === Declarations ===
  VariableDeclaration,
  FunctionDeclaration,
  OperatorDeclaration,

  FunctionCall,
  FunctionParameter,
  NativeFunctionDeclaration,
  TypeDeclaration,
  ParameterDeclaration,

  CallExpression,
  BinaryExpression,
  UnaryExpression,
  LiteralExpression,
  AssignmentExpression,

  // === Types ===
  Type,
  TypeReference,
  GenericType,
};

} // namespace core::node
