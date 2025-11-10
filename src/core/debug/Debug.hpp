// #pragma once
// #include "core/token/Descriptors.hpp"
// #include "core/token/Token.hpp"
// #include "core/utils/Utf8.hpp"
// #include <iostream>
// #include <memory>
// #include <string_view>

// namespace lang::debug {

// inline void log_token(const std::shared_ptr<lang::core::Token> &token) {
//   if (!token) {
//     std::cout << "[Token] <null>\n";
//     return;
//   }

//   size_t line  = token->location.line;
//   size_t start = token->location.start;
//   size_t end   = token->location.end;

//   const auto lexeme_utf8 = lang::utils::Utf8Codec::encode(token->lexeme);

//   std::cout << "[Token] Lexeme: '" << lexeme_utf8 << "', Location: (Line: " << line << ", Start: " << start << ", End: " << end << ")\n";
// }

// inline void log_descriptor(const lang::core::TokenDescriptor &descriptor) {
//   std::string_view group;

//   switch (descriptor.group) {
//     case lang::core::TokenGroup::Literal: group = "Literal"; break;
//     case lang::core::TokenGroup::Keyword: group = "Keyword"; break;
//     case lang::core::TokenGroup::Operator: group = "Operator"; break;
//     case lang::core::TokenGroup::Punctuation: group = "Punctuation"; break;
//     case lang::core::TokenGroup::Identifier: group = "Identifier"; break;
//     case lang::core::TokenGroup::Type: group = "Type"; break;
//     default: group = "Unknown"; break;
//   }

//   std::cout << "[Descriptor] -> Type: (" << descriptor.name << ", Group: " << group << ")\n";
// }

// } // namespace lang::debug
