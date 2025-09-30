#pragma once
#include <memory>
#include <string>

struct TokenDescriptor {
  std::string id;
  std::string lexeme;
  std::string type;
};

using DescriptorPtr = std::shared_ptr<TokenDescriptor>;
