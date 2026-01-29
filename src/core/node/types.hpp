#include "core/node/Type.hpp"

struct VoidTypeNode : core::ast::TypeNode {
  VoidTypeNode() : TypeNode(new core::ast::IdentifierNode("Void"), true) { kind = core::ast::NodeKind::Type; }
};

struct NumberTypeNode : core::ast::TypeNode {
  NumberTypeNode() : core::ast::TypeNode(new core::ast::IdentifierNode("Number"), true) { kind = core::ast::NodeKind::Type; }
};

struct StringTypeNode : core::ast::TypeNode {
  StringTypeNode() : core::ast::TypeNode(new core::ast::IdentifierNode("String"), true) { kind = core::ast::NodeKind::Type; }
};

struct BooleanTypeNode : core::ast::TypeNode {
  BooleanTypeNode() : core::ast::TypeNode(new core::ast::IdentifierNode("Bool"), true) { kind = core::ast::NodeKind::Type; }
};

struct Types {
  static NumberTypeNode Number;
  static StringTypeNode String;
  static BooleanTypeNode Bool;
  static VoidTypeNode Void;
};
