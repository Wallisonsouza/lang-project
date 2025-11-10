// #pragma once

// #include "argon/argon_descriptor.hpp"
// #include "core/Token.hpp"
// #include "core/base/HandlerPluginBase.hpp"
// #include <memory>
// #include <sstream>
// #include <stdexcept>

// class StringHandler : public HandlerPlugin {
// public:
//   std::shared_ptr<Token> match(TokenizerContext &context) override {
//     auto stream = context.charStream;

//     if (!stream->hasNext() || (stream->current() != '"' && stream->current() != '\'')) {
//       return nullptr;
//     }

//     char quote   = stream->current();
//     size_t start = stream->position();
//     stream->advance(); // pular a aspa inicial

//     std::string lexeme;
//     bool closed = false;

//     while (stream->hasNext()) {
//       char c = stream->current();

//       if (c == '\\') {
//         stream->advance(); // consumir '\'
//         if (!stream->hasNext())
//           break;

//         char next = stream->current();
//         switch (next) {
//           case 'n': lexeme.push_back('\n'); break;
//           case 't': lexeme.push_back('\t'); break;
//           case '\\': lexeme.push_back('\\'); break;
//           case '"': lexeme.push_back('"'); break;
//           case '\'': lexeme.push_back('\''); break;
//           default: lexeme.push_back(next); break;
//         }

//         stream->advance(); // consumir caractere escapado
//         continue;
//       } else if (c == quote) {
//         closed = true;
//         stream->advance(); // consumir a aspa de fechamento
//         break;
//       } else {
//         lexeme.push_back(c);
//         stream->advance();
//       }
//     }

//     if (!closed) {
//       std::ostringstream oss;
//       oss << "Erro léxico: string não fechada. Início: " << start << ", posição atual: " << stream->position();
//       throw std::runtime_error(oss.str());
//     }

//     auto descriptor = context.descriptors.getById(TokenId::STRING_LITERAL);
//     if (!descriptor) {
//       return nullptr;
//     }

//     return std::make_shared<Token>(descriptor.value(), lexeme, SourceLocation{context.lineStream->position(), start, stream->position()});
//   }
// };
