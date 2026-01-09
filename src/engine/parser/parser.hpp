#pragma once
#include "core/node/Modifier.hpp"
#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement_nodes.hpp"

struct Parser {
  CompilationUnit &unit;

  core::node::TypeNode *parse_type();

private:
  core::node::ExpressionNode *parse_assignment(core::node::ExpressionNode *target);
  core::node::ExpressionNode *finish_call(core::node::ExpressionNode *callee);
  core::node::ExpressionNode *finish_member(core::node::ExpressionNode *base);
  core::node::ExpressionNode *finish_index(core::node::ExpressionNode *base);
  core::node::Modifiers parse_modifiers();

  std::vector<core::node::FunctionParameterNode *> parse_parameter_list();

public:
  core::node::ExpressionNode *parse_path_expression();
  core::node::ExpressionNode *parse_expression();
  core::node::ExpressionNode *parse_postfix_expression();
  core::node::ExpressionNode *parse_primary_expression();
  core::node::ExpressionNode *parse_binary_expression(int min_precedence, core::node::ExpressionNode *lef);

  core::node::StatementNode *parse_statement();
  core::node::StatementNode *parse_import_statement();
  core::node::StatementNode *parse_if_statement();
  core::node::StatementNode *parse_variable_declaration();
  core::node::StatementNode *parse_function_declaration();
  parser::node::BlockNode *parse_block();
  core::node::FunctionParameterNode *parse_function_parameter();

  core::node::Node *call_parser() { return parse_statement(); }

  void generate_ast() {

    while (!unit.tokens.is_end()) {
      auto node = call_parser();
      if (node) {
        unit.ast.add_root(node);
      } else {
        unit.tokens.advance();
      }
    }
  }

  inline void report_expected(DiagnosticCode code, const std::variant<core::token::TokenKind, core::node::NodeKind, std::string> &expected, const core::token::Token *found) {
    DiagnosticContext ctx;

    if (std::holds_alternative<core::token::TokenKind>(expected))
      ctx.set("expected", std::get<core::token::TokenKind>(expected));
    else if (std::holds_alternative<core::node::NodeKind>(expected))
      ctx.set("expected", std::get<core::node::NodeKind>(expected));
    else
      ctx.set("expected", std::get<std::string>(expected));

    // Preenche o found se houver
    if (found && !found->descriptor->name.empty()) {
      ctx.set("found", found->descriptor->kind);
    } else if (found) {
      // fallback se não houver descriptor
      ctx.set("found", unit.source.buffer.get_text(found->slice.span));
    }
    auto slice = unit.tokens.last_slice();
    if (found) { slice = found->slice; }

    unit.diagns.report(Diagnostic{.origin = DiagnosticOrigin::Parser, .code = code, .slice = slice, .context = std::move(ctx)});
  }
};
