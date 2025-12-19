#pragma once
#include "core/CompilationUnit.hpp"
#include "core/module/Scope.hpp"
#include <string>

struct FileUnit {
  std::string path;
  CompilationUnit unit;
  core::Scope scope;

  FileUnit(std::string file_path, CompilationUnit &&compilation_unit) : path(std::move(file_path)), unit(std::move(compilation_unit)), scope(nullptr) {}
};
