#include "engine/CompilationUnit.hpp"
#include "engine/lexer/lexer.hpp"
#include "engine/parser/parser.hpp"

struct ExecutionUnit {
  CompilationUnit &comp_unit;
  Lexer lexer;
  Parser parser;

public:
  ExecutionUnit(CompilationUnit &unit) : comp_unit(unit), lexer(unit), parser(unit) {}

  void execute() {
    lexer.generate_tokens();
    parser.generate_ast();
  }
};