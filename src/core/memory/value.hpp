#pragma once
#include <functional>
#include <string>
#include <variant>
#include <vector>

enum class ValueKind { Number, Boolean, String, Null, Void, NativeFunction };

struct NullValue {};
struct VoidValue {};

namespace parser::node {
struct FunctionDeclarationNode;
}

struct RuntimeScope;

struct UserFunction {
  parser::node::FunctionDeclarationNode *node;
  RuntimeScope *captured_scope;

  UserFunction(parser::node::FunctionDeclarationNode *n, RuntimeScope *scope) : node(n), captured_scope(scope) {}
};

struct Value {

  using NativeFunction = std::function<Value(const std::vector<Value> &)>;

  using Storage = std::variant<double, bool, std::string, NullValue, VoidValue, NativeFunction, UserFunction>;

  Storage data;

  static Value Number(double v) { return Value{v}; }
  static Value Boolean(bool b) { return Value{b}; }
  static Value String(std::string s) { return Value{std::move(s)}; }
  static Value Null() { return Value{NullValue{}}; }
  static Value Void() { return Value{VoidValue{}}; }
  static Value Native(NativeFunction fn) { return Value{std::move(fn)}; }
  static Value User(parser::node::FunctionDeclarationNode *node, RuntimeScope *scope) { return Value{UserFunction(node, scope)}; }

  double get_number() const { return std::get<double>(data); }

  bool get_boolean() const { return std::get<bool>(data); }

  const std::string &get_string() const { return std::get<std::string>(data); }

  const NativeFunction &get_native() const { return std::get<NativeFunction>(data); }

  UserFunction &get_user_function() { return std::get<UserFunction>(data); }

  std::string convert_to_string() const {
    if (std::holds_alternative<double>(data)) return std::to_string(std::get<double>(data));
    if (std::holds_alternative<bool>(data)) return std::get<bool>(data) ? "true" : "false";
    if (std::holds_alternative<std::string>(data)) return std::get<std::string>(data);
    if (std::holds_alternative<NativeFunction>(data)) return "<native function>";
    return "void";
  }

  bool as_bool() const {
    if (std::holds_alternative<bool>(data)) { return std::get<bool>(data); }
    if (std::holds_alternative<double>(data)) { return std::get<double>(data) != 0.0; }
    if (std::holds_alternative<std::string>(data)) { return !std::get<std::string>(data).empty(); }
    if (std::holds_alternative<NullValue>(data)) return false;
    if (std::holds_alternative<VoidValue>(data)) return false;
    if (std::holds_alternative<NativeFunction>(data)) return true;
    return false;
  }

  bool is_user_function() const { return std::holds_alternative<UserFunction>(data); }
  bool is_native_function() const { return std::holds_alternative<NativeFunction>(data); }
};
