#include <functional>
#include <string>
#include <variant>
#include <vector>

enum class ValueKind { Number, Boolean, String, Null, Void, NativeFunction };

struct NullValue {};
struct VoidValue {};

struct Value {

  using NativeFn = std::function<Value(const std::vector<Value> &)>;

  using Storage =
      std::variant<double, bool, std::string, NullValue, VoidValue, NativeFn>;

  Storage data;

  static Value Number(double v) { return Value{v}; }
  static Value Boolean(bool b) { return Value{b}; }
  static Value String(std::string s) { return Value{std::move(s)}; }
  static Value Null() { return Value{NullValue{}}; }
  static Value Void() { return Value{VoidValue{}}; }
  static Value Native(NativeFn fn) { return Value{std::move(fn)}; }

  double get_number() const { return std::get<double>(data); }

  bool get_boolean() const { return std::get<bool>(data); }

  const std::string &get_string() const { return std::get<std::string>(data); }

  const NativeFn &get_native() const { return std::get<NativeFn>(data); }

  std::string convert_to_string() const {
    if (std::holds_alternative<double>(data))
      return std::to_string(std::get<double>(data));
    if (std::holds_alternative<bool>(data))
      return std::get<bool>(data) ? "true" : "false";
    if (std::holds_alternative<std::string>(data))
      return std::get<std::string>(data);
    if (std::holds_alternative<NativeFn>(data))
      return "<native function>";
    return "null";
  }
};
