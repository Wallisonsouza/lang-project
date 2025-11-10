
// #pragma once

// #include "core/base/Context.hpp"
// #include "core/base/HandlerPluginBase.hpp"
// #include "core/context/descriptor_context.hpp"
// #include <memory>

// std::shared_ptr<DescriptorContext> create_descriptor();
// std::unique_ptr<Context<HandlerPlugin>> createArgonHandlerContext();

// inline std::unique_ptr<Context<StructuralPlugin>> createArgonStructuralContext() {

//   auto context = std::make_unique<Context<StructuralPlugin>>();

//   context->addContext(0, std::make_unique<FunctionCallStructuralPlugin>());

//   return context;
// }

// inline std::shared_ptr<Environment> createStandardConsoleLibrarie() {
//   auto env = std::make_shared<Environment>();

//   auto printFunc = std::make_shared<NativeFunctionNode>([](const std::vector<LanguagePrimitives> &args) -> LanguagePrimitives {
//     for (const auto &arg : args) {
//       std::visit([](auto &&val) { std::cout << val << " "; }, arg);
//     }
//     std::cout << std::endl;
//     return 0;
//   });

//   env->exportSymbol("log", printFunc);

//   auto errorFunc = std::make_shared<NativeFunctionNode>([](const std::vector<LanguagePrimitives> &args) -> LanguagePrimitives {
//     for (const auto &arg : args) {
//       std::visit([](auto &&val) { std::cerr << val << " "; }, arg);
//     }
//     std::cerr << std::endl;
//     return 0;
//   });

//   env->exportSymbol("error", errorFunc);

//   auto readLineFunc = std::make_shared<NativeFunctionNode>([](const std::vector<LanguagePrimitives> &) -> LanguagePrimitives {
//     std::string input;
//     std::getline(std::cin, input);
//     return input;
//   });

//   env->exportSymbol("readLine", readLineFunc);

//   auto clearFunc = std::make_shared<NativeFunctionNode>([](const std::vector<LanguagePrimitives> &) -> LanguagePrimitives {
// #ifdef _WIN32
//     system("cls");
// #else
//     system("clear");
// #endif
//     return 0;
//   });
//   env->exportSymbol("clear", clearFunc);

//   return env;
// }

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