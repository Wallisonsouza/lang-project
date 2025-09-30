#pragma once
#include "core/TokenDescriptor.hpp"
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

class DescriptorContext {
public:
  DescriptorContext() = default;

  void addDescriptor(const std::string &id, const std::string &lexeme, const std::string &type) {
    auto descriptor = std::make_shared<TokenDescriptor>(TokenDescriptor{id, lexeme, type});
    tokens[id] = descriptor;
    lexemeIndex[lexeme] = descriptor;
  }

  std::optional<std::shared_ptr<TokenDescriptor>> getById(const std::string &id) const {
    if (auto it = tokens.find(id); it != tokens.end()) {
      return it->second;
    }
    return std::nullopt;
  }

  std::optional<std::shared_ptr<TokenDescriptor>> getByLexeme(const std::string &lexeme) const {
    if (auto it = lexemeIndex.find(lexeme); it != lexemeIndex.end()) {
      return it->second;
    }
    return std::nullopt;
  }

  bool updateLexeme(const std::string &id, const std::string &newLexeme) {
    if (auto it = tokens.find(id); it != tokens.end()) {

      lexemeIndex.erase(it->second->lexeme);
      it->second->lexeme = newLexeme;
      lexemeIndex[newLexeme] = it->second;
      return true;
    }
    return false;
  }

  void merge(const DescriptorContext &other) {
    for (auto &[id, desc] : other.tokens) {
      tokens[id] = desc;
      lexemeIndex[desc->lexeme] = desc;
    }
  }

private:
  std::unordered_map<std::string, std::shared_ptr<TokenDescriptor>> tokens;
  std::unordered_map<std::string, std::shared_ptr<TokenDescriptor>> lexemeIndex;
};