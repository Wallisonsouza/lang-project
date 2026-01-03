#pragma once
#include <cstdint>

namespace core::token {
enum class TokenKind : uint8_t {
  Static,
  Mut,
  Public,
  Private,
  Invalid,

  OpenBracket,
  CloseBracket,

  // Define um enum class chamado TokenKind que representa diferentes tipos de
  // tokens na análise léxica.
  // ': uint8_t' força o enum a usar apenas 1 byte de memória por valor.
  Value,

  FunctionKeyword,
  OperatorKeyword,
  ReturnKeyword,
  UseKeyword,
  AsKeyword,

  Function,    // Representa a palavra-chave 'function' em uma linguagem.
  If,          // Representa a palavra-chave 'if'.
  Else,        // Representa a palavra-chave 'else'.
  While,       // Representa a palavra-chave 'while'.
  For,         // Representa a palavra-chave 'for'.
  Return,      // Representa a palavra-chave 'return'.
  Comma,       // Representa a vírgula ','.
  DoubleQuote, // Representa uma aspa dupla '"'.
  SingleQuote, // Representa uma aspa simples '\''.
  Variable,    // Representa a declaração de uma variável.
  Colon,       // Representa o caractere ':'.
  DoubleColon,
  Arrow,
  Plus,        // Representa o operador de adição '+'.
  Minus,       // Representa o operador de subtração '-'.
  Star,        // Representa o operador de multiplicação '*'.
  Slash,       // Representa o operador de divisão '/'.
  Assign,      // Representa o operador de atribuição '='.
  Equals,      // Representa o operador de igualdade '=='.
  Ternary,     // Representa o operador ternário '?'.
  LessThan,    // Representa o operador '<'.
  GreaterThan, // Representa o operador '>'.

  OpenParen,  // Representa o parêntese esquerdo '('.
  Space,      // Representa um espaço em branco.
  CloseParen, // Representa o parêntese direito ')'.

  OpenBrace,  // Representa a chave esquerda '{'.
  CloseBrace, // Representa a chave direita '}'.
  Semicolon,  // Representa o ponto e vírgula ';'.
  Dot,
  Alias,      // Representa um alias (como 'type alias' em algumas linguagens).
  Identifier, // Representa nomes de variáveis, funções ou outros
              // identificadores.
  NumberLiteral, // Representa um literal numérico, como 42 ou 3.14.
  StringLiteral, // Representa um literal de string, como "texto".
  NullLiteral,   // Representa o valor nulo 'null'.
  CharLiteral,   // Representa um literal de caractere, como 'a'.
  BoolLiteral,   // Representa um literal booleano: true ou false.
  EndOfFile, // Representa o fim do arquivo, usado para indicar que não há mais
             // tokens.
};
}
