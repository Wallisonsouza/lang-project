#pragma once

#include "core/CompilationUnit.hpp"
#include "core/Context.hpp"
#include "core/text/TextSpan.hpp"

namespace helper {
class TokenMatchHelper {
public:
  static bool has_prefix(CompilationUnit &unit, const core::source::Span &span) {
    auto view = span.view();
    return unit.context.descriptor_table.has_prefix(view) || unit.alias_table.has_prefix(view);
  }
};

} // namespace helper