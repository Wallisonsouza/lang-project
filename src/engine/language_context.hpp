#pragma once
#include "core/memory/module_manager.hpp"
#include "core/module/scope.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"

struct LanguageContext {
  core::table::DescriptorTable descriptor_table;
  core::table::PrecedenceTable precedence_table;
  core::ModuleManager modules;
  core::Scope root_scope;

  LanguageContext() : root_scope(nullptr) {}
};
