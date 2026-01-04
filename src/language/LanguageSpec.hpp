#pragma once

#include "core/module/scope.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"

namespace ayla::language {

struct LanguageSpec {
  core::table::DescriptorTable descriptor_table;
  core::table::PrecedenceTable precedence_table;
  core::Scope root_scope;

  LanguageSpec() : root_scope(nullptr) {}
};

} // namespace ayla::language