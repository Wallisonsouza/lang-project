#include "core/node/Type.hpp"

struct VoidTypeNode : core::node::TypeNode {
  VoidTypeNode() : TypeNode(new core::node::IdentifierNode("Void"), true) {
    kind = core::node::NodeKind::Type;
  }
};

struct NumberTypeNode : core::node::TypeNode {
  NumberTypeNode()
      : core::node::TypeNode(new core::node::IdentifierNode("Number"), true) {
    kind = core::node::NodeKind::Type;
  }
};

struct StringTypeNode : core::node::TypeNode {
  StringTypeNode()
      : core::node::TypeNode(new core::node::IdentifierNode("String"), true) {
    kind = core::node::NodeKind::Type;
  }
};

struct BooleanTypeNode : core::node::TypeNode {
  BooleanTypeNode()
      : core::node::TypeNode(new core::node::IdentifierNode("Bool"), true) {
    kind = core::node::NodeKind::Type;
  }
};

struct Types {
  static NumberTypeNode Number;
  static StringTypeNode String;
  static BooleanTypeNode Bool;
  static VoidTypeNode Void;
};
