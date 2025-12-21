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

  // === Statements ===
  Block,
  IfStatement,
  WhileStatement,
  ForStatement,
  ReturnStatement,
  ExpressionStatement,

  // === Declarations ===
  VariableDeclaration,
  FunctionDeclaration,
  FunctionCall,
  FunctionParameter,
  NativeFunction,
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
