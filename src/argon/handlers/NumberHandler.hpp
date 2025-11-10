// #pragma once

// #include "core/LangData.hpp"
// #include "core/plugin/Plugin.hpp"
// #include "core/token/Token.hpp"
// #include "core/utils/Unicode.hpp"
// #include <memory>
// #include <string>

// namespace argon::plugins::handlers {

// class NumberHandler : public lang::core::Plugin {
// public:
//   std::shared_ptr<lang::core::Token> exec(lang::core::LangData &data, lang::utils::Stream &stream) override {
//     const size_t start = stream.position();
//     char32_t c         = stream.current();

//     if (!lang::utils::Unicode::isDigit(c)) {
//       return nullptr;
//     }

//     std::u32string lexeme;

//     while (!stream.isEOF() && lang::utils::Unicode::isDigit(stream.current())) {
//       lexeme += stream.current();
//       stream.next();
//     }

//     lang::core::TokenType numberType{"Number", lang::core::TokenGroup::Literal};
//     auto descriptor = std::make_shared<lang::core::DescriptorEntry>(lexeme, numberType);

//     return std::make_shared<lang::core::Token>(descriptor, lexeme, lang::core::Location{data.line, start, stream.position()});
//   }
// };

// } // namespace argon::plugins::handlers
