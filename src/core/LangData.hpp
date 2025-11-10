#pragma once

#include "core/plugin/Plugin.hpp"
#include "core/plugin/PluginRegistry.hpp"
#include "core/token/TokenTable.hpp"

namespace lang::core {

struct LangData {
  size_t line = 0;

  TokenTable descriptors;
  PluginRegistry handlers;
  PluginRegistry solvers;
};

inline LangData makeLangData() { return LangData{}; }

} // namespace lang::core
