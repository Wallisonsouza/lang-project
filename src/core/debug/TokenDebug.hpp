#include "core/debug/Console.hpp"
#include "core/table/TokenGroupDebug.hpp"
#include "core/table/TokenKindTable.hpp"
#include "core/token/Token.hpp"
#include "core/utils/Utf8.hpp"

#include <string>
namespace lang::debug {
class TokenDebug {
public:
  static void print_token(const lang::core::Token &token) {
    std::string kind  = lang::debug::TokenKindTable::kind_map.at(token.descriptor->kind);
    std::string group = lang::debug::TokenGroupDebug::group_map.at(token.descriptor->group);

    lang::debug::Console::debug("Token(", kind, ",", group, ",\"", lang::utils::Utf8::toUtf8(token.lexeme), "\", Line:", token.location.line, ", Start:", token.location.start,
                                ", End:", token.location.end, ")");
  }
};
} // namespace lang::debug