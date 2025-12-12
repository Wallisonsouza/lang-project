#pragma once

#include "core/LangData.hpp"
#include "core/text/TextStream.hpp"
#include "helper/TokenMatchHelper.hpp"
#include "lexer/plugin.hpp"

namespace lexer::plugins {

class OperatorPlugin : public lexer::LexerPlugin {
public:
  std::optional<core::token::Token> match(core::text::TextStream &stream,
                                          core::LangData &data) override {
    if (stream.eof())
      return std::nullopt;

    auto initial_state = stream.get_state();
    core::text::TextStream::State last_valid_state = initial_state;
    core::token::TokenDescriptor *last_desc = nullptr;

    auto &buf = data.buffer;

    while (!stream.eof()) {

      auto span = stream.span_from(initial_state, stream.get_state());

      if (!helper::TokenMatchHelper::has_prefix(data, span.start,
                                                span.length()))
        break;

      if (auto *desc =
              helper::TokenMatchHelper::resolve_descriptor(data, span)) {
        last_desc = desc;
        last_valid_state = stream.get_state();
      }

      stream.advance();
    }

    if (!last_desc)
      return std::nullopt;

    stream.rollback(last_valid_state);

    core::text::TextSpan final_span =
        stream.span_from(initial_state, last_valid_state);

    return core::token::Token(last_desc, final_span);
  }
};

} // namespace lexer::plugins
