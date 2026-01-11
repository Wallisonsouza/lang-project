#pragma once
#include <cstdint>

enum class NodeFlags : uint32_t {
  None = 0,
  HasError = 1 << 0,
  Synthetic = 1 << 1,
  Constant = 1 << 2,
  Used = 1 << 3,
};

inline NodeFlags operator|(NodeFlags a, NodeFlags b) { return static_cast<NodeFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b)); }

inline NodeFlags &operator|=(NodeFlags &a, NodeFlags b) {
  a = a | b;
  return a;
}

inline NodeFlags operator&(NodeFlags a, NodeFlags b) { return static_cast<NodeFlags>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b)); }

inline bool has_flag(NodeFlags flags, NodeFlags test) { return (flags & test) != NodeFlags::None; }