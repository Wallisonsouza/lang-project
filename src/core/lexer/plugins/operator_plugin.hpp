#pragma once

#include "core/LangData.hpp"
#include "core/helper/TokenMatchHelper.hpp"
#include "core/lexer/plugin.hpp"

namespace interpreter::lexer::plugins {

class OperatorPlugin : public interpreter::lexer::LexerPlugin {
public:
  bool match(TextStream &stream, interpreter::core::LangData &data) override {
    if (stream.eof()) return false;

    auto initial_state = stream.get_state();
    TextStream::State last_valid_state = initial_state;
    TokenDescriptor *last_desc = nullptr;

    auto &buf = data.buffer;

    while (!stream.eof()) {

      auto span = stream.span_from(initial_state, stream.get_state());

      if (!helper::TokenMatchHelper::has_prefix(data, span.start, span.length())) break;

      if (auto *desc = helper::TokenMatchHelper::resolve_descriptor(data, span)) {
        last_desc = desc;
        last_valid_state = stream.get_state();
      }

      stream.advance();
    }

    if (!last_desc) return false;

    TextSpan final_span = stream.span_from(initial_state, last_valid_state);
    data.make_token(last_desc, final_span);

    stream.rollback(last_valid_state);

    return true;
  }
};

} // namespace interpreter::lexer::plugins
