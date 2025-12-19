#pragma once

#include "core/module/ModuleRegistry.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"

namespace core {

struct Context {
  table::DescriptorTable descriptor_table;
  table::PrecedenceTable precedence_table;
  ModuleRegistry module_registry;
};

} // namespace core
