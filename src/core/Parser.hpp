#pragma once
#include "Ast.hpp"
#include "Stream.hpp"
#include "Token.hpp"
#include <algorithm>
#include <memory>
#include <vector>

using ASTNodeList = std::vector<std::unique_ptr<ASTNode>>;

struct ParserPluginBase {
  virtual ~ParserPluginBase() = default;

  virtual std::unique_ptr<ASTNode> match(Stream<Token> &tokens,
                                         size_t &pos) = 0;
};

using ParserPluginPtr = std::unique_ptr<ParserPluginBase>;

struct ParserPluginEntry {
  int priority;
  ParserPluginPtr plugin;
};

class Parser {
public:
  void addPlugin(int priority, ParserPluginPtr plugin) {
    plugins.push_back({priority, std::move(plugin)});
    std::sort(plugins.begin(), plugins.end(), [](const auto &a, const auto &b) {
      return a.priority > b.priority;
    });
  }

  ASTNodeList parse(Stream<Token> &tokens) {
    ASTNodeList ast;
    size_t pos = 0;

    while (tokens.hasNext()) {
      bool matched = false;

      for (ParserPluginEntry &entry : plugins) {
        std::unique_ptr<ASTNode> node = entry.plugin->match(tokens, pos);
        if (node) {
          ast.push_back(std::move(node));
          matched = true;
          break;
        }
      }

      if (!matched)
        tokens.advance();
    }

    return ast;
  }

private:
  std::vector<ParserPluginEntry> plugins;
};
