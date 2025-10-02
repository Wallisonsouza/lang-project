/* 
#include "core/Token.hpp"
#include <vector>

class StructuralAnalyzer {
public:
  static std::vector<std::unique_ptr<PreNode>> analyze(std::vector<Token> &tokens, ) {
    std::vector<std::unique_ptr<PreNode>> nodes;

    size_t i = 0;
    while (i < tokens.size()) {
      const Token &tok = tokens[i];

      if (tok.descriptor->type == DescriptorType::IDENTIFIER) {
        // Exemplo simples: detectar chamada de função
        if (i + 1 < tokens.size() && tokens[i + 1].descriptor->id == DescriptorID::OPEN_PAREN) {
          auto callNode = std::make_unique<FunctionCallStructuralNode>();
          callNode->name = tok.lexeme;

          i += 2; // pula identifier + '('

          // coletar argumentos brutos até ')'
          while (i < tokens.size() && tokens[i].descriptor->id != DescriptorID::CLOSE_PAREN) {
            callNode->rawArgs.push_back(tokens[i]);
            ++i;
          }
          ++i; // pula ')'

          nodes.push_back(std::move(callNode));
          continue;
        }
      }

      // outros casos: literais, expressões etc. podem ser tratados aqui

      ++i;
    }

    return nodes;
  }
};
 */