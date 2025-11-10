/* #pragma once
#include "argon/argon_descriptor.hpp"
#include "argon/nodes/FloatLiteralNode.hpp"
#include "argon/nodes/IntLiteralNode.hpp"
#include "argon/nodes/StringLiteralNode.hpp"
#include "argon/nodes/binary_expression_node.hpp"
#include "core/Parser.hpp"
#include "core/Token.hpp"
#include "core/ast.hpp"
#include <iostream>

class BinaryExpressionGenerator : public ParserPluginBase {
public:
  std::unique_ptr<Node> match(Stream<Token> &stream) override {

    stream.saveState();

    // passo 1
    if (!stream.hasNext()) {
      stream.rollback();
      return nullptr;
    }
    Token leftToken = stream.current();
    if (leftToken.descriptor->type != DescriptorType::LITERAL) {
      return nullptr;
    }

    stream.advance();

    // passo 2
    if (!stream.hasNext()) {
      stream.rollback();
      return nullptr;
    }
    Token opToken = stream.current();
    if (opToken.descriptor->type != DescriptorType::OPERATOR) {
      stream.rollback();
      return nullptr;
    }
    stream.advance();

    // passo 3
    if (!stream.hasNext()) {
      stream.rollback();
      return nullptr;
    }
    Token rightToken = stream.current();
    if (rightToken.descriptor->type != DescriptorType::LITERAL) {
      stream.rollback();
      return nullptr;
    }
    stream.advance();

    // passo 4
    auto leftNode = getNodeFromToken(leftToken);
    auto rightNode = getNodeFromToken(rightToken);

    if (!leftNode || !rightNode) {
      stream.rollback();
      return nullptr;
    }

    // Converte token operador em BinaryOp
    BinaryOp binaryOp = mapOperator(opToken);

    std::cout << opToken.toString();

    return std::make_unique<BinaryExpression>(std::move(leftNode), std::move(rightNode), binaryOp);
  }

private:
  std::unique_ptr<Node> getNodeFromToken(Token &token) {
    if (token.descriptor->id == DescriptorID::INT_LITERAL)
      return std::make_unique<IntLiteralNode>(std::stoi(token.lexeme));
    else if (token.descriptor->id == DescriptorID::FLOAT_LITERAL)
      return std::make_unique<FloatLiteralNode>(std::stof(token.lexeme));
    else if (token.descriptor->id == DescriptorID::STRING_LITERAL)
      return std::make_unique<StringLiteralNode>(token.lexeme);
    else
      return nullptr;
  }

  BinaryOp mapOperator(const Token &tok) {
    if (tok.descriptor->id == DescriptorID::PLUS)
      return BinaryOp::Add;
    else if (tok.descriptor->id == DescriptorID::MINUS)
      return BinaryOp::Subtract;
    else if (tok.descriptor->id == DescriptorID::MULTIPLY)
      return BinaryOp::Multiply;
    else if (tok.descriptor->id == DescriptorID::DIVIDE)
      return BinaryOp::Divide;
    else
      throw std::runtime_error("Operador não suportado");
  }
};
 */