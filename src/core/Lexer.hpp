#pragma once
#include "HandlerBase.hpp"
#include "core/Stream.hpp"
#include "core/Token.hpp"
#include <memory>
#include <string>
#include <vector>

struct HandlerEntry {
  int priority;
  std::unique_ptr<HandlerBase> handler;
};

class Lexer {
public:
  explicit Lexer(const std::string &source);

  void addHandler(int priority, std::unique_ptr<HandlerBase> handler);

  std::vector<Token> tokenize();

private:
  Stream<char> stream;
  std::vector<HandlerEntry> handlers;

  void skipWhitespace();
};
