#pragma once
#include "core/AST.hpp"
#include "core/CompilationUnit.hpp"
#include "core/TokenStream.hpp"
#include "core/node/Type.hpp"
#include "parser/node/literal_nodes.hpp"
#include "parser/node/operator_nodes.hpp"
#include "utils/Utf8.hpp"
#include <string>

class ExpressionParser {
public:
  core::node::ExpressionNode *parse(AST &ast, CompilationUnit &unit, TokenStream &stream) { return parse_binary_expression(ast, unit, stream, 0); }

private:
  core::node::ExpressionNode *parse_binary_expression(AST &ast, CompilationUnit &unit, TokenStream &stream, int min_precedence) {

    auto left = parse_primary(ast, unit, stream);
    if (!left) return nullptr;

    while (true) {
      auto tok = stream.peek();
      if (!tok) break;

      int prec = unit.context.precedence_table.get_precedence(tok->descriptor->kind);
      if (prec < min_precedence) break;

      bool right_assoc = unit.context.precedence_table.is_right_associative(tok->descriptor->kind);

      stream.advance();

      int next_min_prec = right_assoc ? prec : prec + 1;

      auto right = parse_binary_expression(ast, unit, stream, next_min_prec);
      if (!right) return nullptr;

      left = ast.create_node<node::BinaryExpressionNode>(left, unit.source.buffer.get_text(tok->span), right);
    }

    return left;
  }

  core::node::ExpressionNode *parse_primary(AST &ast, CompilationUnit &unit, TokenStream &stream) {
    stream.push_checkpoint();
    auto tok = stream.consume();
    if (!tok || !tok->descriptor) {
      stream.rollback_checkpoint();
      return nullptr;
    }

    core::node::ExpressionNode *result = nullptr;

    switch (tok->descriptor->kind) {
    case core::token::TokenKind::NumberLiteral: {
      auto text = unit.source.buffer.get_text(tok->span);
      double value = std::stod(utils::Utf::utf32to8(text));
      result = ast.create_node<node::NumberLiteralNode>(value);
      break;
    }
    case core::token::TokenKind::StringLiteral: {
      auto str = unit.source.buffer.get_text(tok->span);
      result = ast.create_node<node::StringLiteralNode>(str);
      break;
    }
    case core::token::TokenKind::Identifier: {
      auto name = unit.source.buffer.get_text(tok->span);
      result = ast.create_node<node::IdentifierNode>(name);
      break;
    }

    case core::token::TokenKind::OpenParen: {
      result = parse(ast, unit, stream);
      tok = stream.consume();
      if (!result || !tok || tok->descriptor->kind != core::token::TokenKind::CloseParen) {
        stream.rollback_checkpoint();
        return nullptr;
      }
      break;
    }
    default: stream.rollback_checkpoint(); return nullptr;
    }

    stream.discard_checkpoint();
    return result;
  }
};