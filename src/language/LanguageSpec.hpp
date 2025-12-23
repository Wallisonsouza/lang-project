#pragma once

#include "core/module/ModuleRegistry.hpp"
#include "core/table/AliasTable.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"

namespace ayla::language {

struct LanguageSpec {
  core::table::DescriptorTable descriptor_table;
  core::table::PrecedenceTable precedence_table;
  core::ModuleRegistry module_registry;
  core::table::AliasTable alias_table{descriptor_table};

  core::Scope root_scope;

  LanguageSpec() : root_scope(nullptr) {}
};

} // namespace ayla::language