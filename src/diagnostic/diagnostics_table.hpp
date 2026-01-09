#pragma once
#include "diagnostic/diagnostic_code.hpp"
#include <unordered_map>

struct DiagnosticTemplate {
  const char *title;
  const char *message;
  const char *help;
};

static const std::unordered_map<DiagnosticCode, DiagnosticTemplate> DIAG_PT_BR = {
    {DiagnosticCode::UnexpectedToken, {"Erro de sintaxe", "Token inesperado '{found}'", "Verifique a sintaxe e os tokens próximos"}},
    {DiagnosticCode::ExpectedToken, {"Erro de sintaxe", "Esperado '{expected}' mas encontrado '{found}'", "Confira se você digitou o token correto"}},
    {DiagnosticCode::ExpectedIdentifier, {"Erro de sintaxe", "Esperado um identificador mas encontrado '{found}'", "Um identificador é um nome válido de variável ou função"}},
    {DiagnosticCode::ExpectedType, {"Erro de tipo", "Esperado um tipo mas encontrado '{found}'", "Verifique se você declarou o tipo corretamente"}},
    {DiagnosticCode::ExpectedExpression, {"Erro de sintaxe", "Esperado uma expressão", "Uma expressão válida é necessária aqui"}},
    {DiagnosticCode::ExpectedColon, {"Erro de sintaxe", "Esperado {expected}", "Lembre-se de usar ':' após o identificador"}},
    {DiagnosticCode::ExpectedDoubleColon, {"Erro de sintaxe", "Esperado '::'", "O operador de escopo '::' é necessário"}},
    {DiagnosticCode::UndeclaredSymbol, {"Erro semântico", "Símbolo '{found}' não declarado", "Verifique se você declarou a variável ou importou o módulo"}},
    {DiagnosticCode::NotCallable, {"Erro semântico", "O símbolo '{found}' não é chamável", "Certifique-se de que você está chamando uma função ou método"}},
    {DiagnosticCode::UnterminatedString, {"Erro léxico", "String não terminada", "As aspas da string devem ser fechadas"}},
    {DiagnosticCode::ModuleNotFound, {"Erro de módulo", "Módulo '{found}' não encontrado", "Verifique o caminho do módulo ou se ele foi importado corretamente"}},
    {DiagnosticCode::Custom, {"Erro", "{message}", ""}}};
