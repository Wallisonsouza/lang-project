#pragma once

#include "engine/CompilationUnit.hpp"
#include "language/LanguageSpec.hpp"

namespace ayla::engine {

class Engine {
public:
  explicit Engine(const language::LanguageSpec &lang);

  CompilationUnit compile(core::source::Source &source);

private:
  const language::LanguageSpec &language;
};

} // namespace ayla::engine
