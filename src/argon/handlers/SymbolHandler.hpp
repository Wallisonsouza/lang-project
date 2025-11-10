#pragma once
#include "core/LangData.hpp"
#include "core/plugin/Plugin.hpp"
#include "core/utils/Stream.hpp"
#include "core/utils/TextStream.hpp"
#include <memory>
#include <string>

namespace argon::plugins {

class UniqueCharHandler final : public lang::core::Plugin {
public:
  std::shared_ptr<lang::core::Token> exec(lang::core::LangData &data, lang::utils::TextStream &stream) override {
    const size_t start = stream.position();

    auto current_char = stream.current();
    if (!current_char) {
      return nullptr;
    }

    std::u32string lexeme(1, *current_char);

    auto descriptor = data.descriptors.get_descriptor(lexeme);
    if (!descriptor) {
      return nullptr;
    }

    const auto &group = descriptor->group;
    if (group != TokenGroup::Operator && group != TokenGroup::Punctuation) {
      return nullptr;
    }

    stream.advance();

    auto location = lang::core::Location{data.line, start, stream.position()};
    return std::make_shared<lang::core::Token>(descriptor, lexeme, location);
  }
};

} // namespace argon::plugins
