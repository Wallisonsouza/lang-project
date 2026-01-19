#pragma once

namespace core::node {

enum class NodeKindBase { Expression, Statement, Type, Pattern, Unknown };

enum class NodeKind {
  // === Base ===
  Unknown = 0,
  NumberLiteral = 1,
  StringLiteral = 2,
  BooleanLiteral = 3,
  CharLiteral = 4,
  NullLiteral = 5,
  Identifier = 6,
  PathExpression = 7,

  // === Statements ===
  MemberAccess = 8,
  IndexAccess = 9,
  BlockStatement = 10,
  IfStatement = 11,
  WhileStatement = 12,
  ForStatement = 13,
  ReturnStatement = 14,
  ExpressionStatement = 15,
  Import = 16,

  // === Declarations ===
  VariableDeclaration = 17,
  FunctionDeclaration = 18,
  OperatorDeclaration = 19,

  FunctionCall = 20,
  FunctionParameter = 21,
  NativeFunctionDeclaration = 22,
  TypeDeclaration = 23,
  ParameterDeclaration = 24,

  CallExpression = 25,
  BinaryExpression = 26,
  UnaryExpression = 27,
  LiteralExpression = 28,
  AssignmentExpression = 29,

  // === Types ===
  Type = 30,
  TypeReference = 31,
  GenericType = 32,
  Assignment = 33,
  Pattern = 34,
  Error = 35,
  ParameterList = 36,
};

} // namespace core::node
