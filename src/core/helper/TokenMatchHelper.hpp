#pragma once

#include "core/LangData.hpp"
#include "core/token/TokenDescriptor.hpp"
#include <string_view>

namespace interpreter::helper {
class TokenMatchHelper {
public:
  static TokenDescriptor *resolve_descriptor(interpreter::core::LangData &data, const std::u32string_view &lexeme) {

    if (TokenDescriptor *d = data.token_table.lookup_by_name(lexeme)) { return d; }

    if (TokenDescriptor *a = data.alias_table.lookup_by_name(lexeme)) { return a; }

    return nullptr;
  }

  static TokenDescriptor *resolve_descriptor(interpreter::core::LangData &data, const TextSpan &span) {
    const auto &buffer = data.buffer;
    size_t len = span.length();
    std::u32string_view view(buffer.u32().data() + span.start, len);

    if (TokenDescriptor *td = data.token_table.lookup_by_name(view)) return td;
    if (TokenDescriptor *alias = data.alias_table.lookup_by_name(view)) return alias;

    return nullptr;
  }

  // static TokenDescriptor *resolve_descriptor(interpreter::core::LangData &data, size_t begin, size_t length) {
  //   auto &buffer = data.buffer;
  //   std::u32string_view view(&buffer.text[begin], length);
  //   if (TokenDescriptor *td = data.token_table.lookup_by_name(view)) return td;
  //   if (TokenDescriptor *alias = data.alias_table.lookup_by_name(view)) return alias;
  //   return nullptr;
  // }

  static bool has_prefix(interpreter::core::LangData &data, const TextSpan &span) {
    const auto &buffer = data.buffer;
    size_t len = span.length();
    std::u32string_view view(buffer.u32().data() + span.start, len);
    return data.token_table.has_prefix(view) || data.alias_table.has_prefix(view);
  }

  static bool has_prefix(interpreter::core::LangData &data, size_t start, size_t length) {
    auto &buffer = data.buffer;
    std::u32string_view view(&buffer.u32()[start], length);
    return data.token_table.has_prefix(view) || data.alias_table.has_prefix(view);
  }
};

} // namespace interpreter::helper