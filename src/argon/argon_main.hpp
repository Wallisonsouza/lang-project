#pragma once

#include "argon/nodes/CallNode.hpp"
#include "core/Environment.hpp"
#include "core/context/descriptor_context.hpp"
#include "core/context/handler_context.hpp"

std::unique_ptr<DescriptorContext> createArgonDesciptorContext();
std::unique_ptr<HandlerContext> createArgonHandlerContext();

std::shared_ptr<Environment> createStandardConsoleLibrarie() {
  auto env = std::make_shared<Environment>();

  auto printFunc = std::make_shared<NativeFunctionNode>([](const std::vector<LanguagePrimitives> &args) -> LanguagePrimitives {
    for (const auto &arg : args) {
      std::visit([](auto &&val) { std::cout << val << " "; }, arg);
    }
    std::cout << std::endl;
    return 0;
  });

  env->exportSymbol("logMessage", printFunc);

  auto errorFunc = std::make_shared<NativeFunctionNode>([](const std::vector<LanguagePrimitives> &args) -> LanguagePrimitives {
    for (const auto &arg : args) {
      std::visit([](auto &&val) { std::cerr << val << " "; }, arg);
    }
    std::cerr << std::endl;
    return 0;
  });

  env->exportSymbol("error", errorFunc);

  auto readLineFunc = std::make_shared<NativeFunctionNode>([](const std::vector<LanguagePrimitives> &) -> LanguagePrimitives {
    std::string input;
    std::getline(std::cin, input);
    return input;
  });

  env->exportSymbol("readLine", readLineFunc);

  auto clearFunc = std::make_shared<NativeFunctionNode>([](const std::vector<LanguagePrimitives> &) -> LanguagePrimitives {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    return 0;
  });
  env->exportSymbol("clear", clearFunc);

  return env;
}
