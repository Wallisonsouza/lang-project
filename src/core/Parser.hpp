#pragma once
#include "Stream.hpp"
#include "Token.hpp"
#include "core/base/Context.hpp"
#include "core/base/StructuralNode.hpp"
#include "core/base/StructuralPlugin.hpp"
#include <memory>
#include <vector>

class Structural {
public:
  static std::vector<std::unique_ptr<StructuralNode>> parse(Stream<Token> &stream, const Context<StructuralPlugin> &context) {

    const auto &entries = context.getAllEntries();

    std::vector<std::unique_ptr<StructuralNode>> structuralNodes;
    while (stream.hasNext()) {
      bool matched = false;

      for (auto &entry : entries) {

        std::unique_ptr<StructuralNode> node = entry.plugin->match(stream);
        if (node) {
          structuralNodes.push_back(std::move(node));
          matched = true;
          break;
        }
      }

      if (!matched)
        stream.advance();
    }

    return structuralNodes;
  }
};
