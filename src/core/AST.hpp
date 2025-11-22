#pragma once
#include <memory>
#include <string>
#include <vector>

enum class NodeKind {
  VarDecl,
  EventHandler,
  IfNode,
};

struct Node {
  NodeKind kind;

  explicit Node(NodeKind kind) : kind(kind) {}
  virtual ~Node() = default;
};

struct VarDecl : Node {
  std::u32string name;
  std::u32string type;
  std::shared_ptr<Node> value;
  bool reactive = false;

  VarDecl(const std::u32string &name, const std::u32string &type, std::shared_ptr<Node> value, bool reactive)
      : Node(NodeKind::VarDecl), name(name), type(type), value(std::move(value)), reactive(reactive) {}
};

struct EventHandler : Node {
  std::u32string event;
  std::u32string selector;
  std::vector<std::shared_ptr<Node>> body;

  EventHandler(const std::u32string &event, const std::u32string &selector, std::vector<std::shared_ptr<Node>> body)
      : Node(NodeKind::EventHandler), event(event), selector(selector), body(std::move(body)) {}
};

struct IfNode : Node {
  std::shared_ptr<Node> condition;
  std::vector<std::shared_ptr<Node>> thenBody;
  std::vector<std::shared_ptr<Node>> elseBody;

  IfNode(std::shared_ptr<Node> condition, std::vector<std::shared_ptr<Node>> thenBody, std::vector<std::shared_ptr<Node>> elseBody = {})
      : Node(NodeKind::IfNode), condition(std::move(condition)), thenBody(std::move(thenBody)), elseBody(std::move(elseBody)) {}
};
