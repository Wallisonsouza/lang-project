#include <cstdint>
#include <string>
#include <vector>

namespace core::node {

enum class Modifier : uint8_t {
  None = 0,
  Value = 1 << 0,
  Static = 1 << 1,
  Mut = 1 << 2,
  Public = 1 << 3,
  Private = 1 << 4,
};

inline Modifier operator|(Modifier a, Modifier b) {
  return static_cast<Modifier>(static_cast<uint8_t>(a) |
                               static_cast<uint8_t>(b));
}

inline bool hasModifier(Modifier mods, Modifier check) {
  return (static_cast<uint8_t>(mods) & static_cast<uint8_t>(check)) != 0;
}

inline std::string modifiersToString(Modifier mods) {
  if (mods == Modifier::None)
    return "None";

  std::vector<std::string> parts;
  if (hasModifier(mods, Modifier::Value))
    parts.push_back("Value");
  if (hasModifier(mods, Modifier::Static))
    parts.push_back("Static");
  if (hasModifier(mods, Modifier::Mut))
    parts.push_back("Mut");
  if (hasModifier(mods, Modifier::Public))
    parts.push_back("Public");
  if (hasModifier(mods, Modifier::Private))
    parts.push_back("Private");

  std::string result;
  for (size_t i = 0; i < parts.size(); ++i) {
    result += parts[i];
    if (i + 1 < parts.size())
      result += " | ";
  }
  return result;
}
} // namespace core::node