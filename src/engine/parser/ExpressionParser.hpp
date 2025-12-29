#pragma once

#include "core/TokenStream.hpp"
#include "core/node/BinaryOp.hpp"
#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "utils/Utf8.hpp"
#include <string>

class ExpressionParser {
public:
  core::node::ExpressionNode *parse_expression(CompilationUnit &unit,
                                               TokenStream &stream) {
    return parse_binary_expression(unit, stream, 0);
  }

  core::node::ExpressionNode *parse_binary_expression(CompilationUnit &unit,
                                                      TokenStream &stream,
                                                      int min_precedence) {

    auto left = parse_primary(unit, stream);
    if (!left)
      return nullptr;

    while (true) {
      auto tok = stream.peek();
      if (!tok)
        break;

      int prec =
          unit.context.precedence_table.get_precedence(tok->descriptor->kind);
      if (prec < min_precedence)
        break;

      bool right_assoc = unit.context.precedence_table.is_right_associative(
          tok->descriptor->kind);

      stream.advance();

      int next_min_prec = right_assoc ? prec : prec + 1;

      auto right = parse_binary_expression(unit, stream, next_min_prec);
      if (!right)
        return nullptr;

      core::node::BinaryOp op;
      switch (tok->descriptor->kind) {
      case core::token::TokenKind::Plus:
        op = core::node::BinaryOp::Add;
        break;
      case core::token::TokenKind::Minus:
        op = core::node::BinaryOp::Subtract;
        break;
      case core::token::TokenKind::Star:
        op = core::node::BinaryOp::Multiply;
        break;
      case core::token::TokenKind::Slash:
        op = core::node::BinaryOp::Divide;
        break;

      default:
        continue;
      }

      left = unit.ast.create_node<parser::node::BinaryExpressionNode>(left, op,
                                                                      right);
    }

    return left;
  }

  core::node::ExpressionNode *parse_primary(CompilationUnit &unit,
                                            TokenStream &stream) {
    stream.push_checkpoint();
    auto tok = stream.consume();
    if (!tok || !tok->descriptor) {
      stream.rollback_checkpoint();
      return nullptr;
    }

    core::node::ExpressionNode *result = nullptr;

    switch (tok->descriptor->kind) {
    case core::token::TokenKind::NumberLiteral: {
      auto text = unit.source.buffer.get_text(tok->slice.span);
      double value = std::stod(utils::Utf::utf32to8(text));
      result = unit.ast.create_node<parser::node::NumberLiteralNode>(value);
      break;
    }
    case core::token::TokenKind::StringLiteral: {
      auto str = unit.source.buffer.get_text(tok->slice.span);
      result = unit.ast.create_node<parser::node::StringLiteralNode>(str);
      break;
    }
    case core::token::TokenKind::Identifier: {
      auto name = unit.source.buffer.get_text(tok->slice.span);
      result = unit.ast.create_node<parser::node::IdentifierNode>(name);
      break;
    }

    case core::token::TokenKind::OpenParen: {
      result = parse_binary_expression(unit, stream, 0);

      tok = stream.consume();
      if (!result || !tok ||
          tok->descriptor->kind != core::token::TokenKind::CloseParen) {
        stream.rollback_checkpoint();
        return nullptr;
      }
      break;
    }

    default:
      stream.rollback_checkpoint();
      return nullptr;
    }

    stream.discard_checkpoint();
    return result;
  }
};