// #pragma once

// #include "core/LangData.hpp"
// #include "core/plugin/Plugin.hpp"
// #include "core/utils/Unicode.hpp"
// #include "core/utils/Utf8.hpp"
// #include <iostream>
// #include <string>

// namespace argon::plugins::handlers {
// class IdentifierHandler : public lang::core::Plugin {
// public:
//   std::shared_ptr<lang::core::Token> exec(lang::core::LangData &data, lang::utils::Stream &stream) override {

//     if (stream.isEOF()) {
//       return nullptr;
//     }

//     std::string lexeme;

//     while (!stream.isEOF() && lang::utils::Unicode::is_letter(stream.current())) {

//       auto c = stream.current();

//       if (lang::utils::Unicode::isWhiteSpace(c)) {
//         stream.next();
//         continue;
//       }

//       std::string out;

//       lang::utils::Utf8Codec::encode(stream.current(), out);
//       std::cout << out << std::endl;
//       stream.next();
//     }
//     return nullptr;
//   }
// };
// } // namespace argon::plugins::handlers
