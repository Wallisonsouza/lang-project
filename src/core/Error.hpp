#pragma once
#include "core/table/AliasTable.hpp"
#include <memory>
#include <string>
#include <vector>

namespace core::error {

class ErrorEngine;

class Error {
public:
  virtual ~Error() = default;

  std::string message;
  std::vector<std::string> suggestions;

  Error(std::string msg, std::vector<std::string> sugg = {}) : message(std::move(msg)), suggestions(std::move(sugg)) {}

  virtual void print(const core::table::AliasTable &alias_table) = 0;
};

class ErrorEngine {
public:
  std::vector<std::unique_ptr<Error>> errors;

  void report(std::unique_ptr<Error> err) { errors.push_back(std::move(err)); }

  void print_all_errors(const core::table::AliasTable &alias_table) {
    for (auto &err : errors) { err->print(alias_table); }
  }
};

} // namespace core::error
