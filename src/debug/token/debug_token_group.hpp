#include "core/token/TokenGroup.hpp"
#include <string>
#include <unordered_map>

namespace debug::token {
inline const std::unordered_map<core::token::TokenGroup, const std::string>
    group_map = {
        {core::token::TokenGroup::Name, "Name"},
        {core::token::TokenGroup::Keyword, "Keyword"},
        {core::token::TokenGroup::Operator, "Operator"},
        {core::token::TokenGroup::Punctuation, "Punctuation"},
        {core::token::TokenGroup::Literal, "Literal"},
        {core::token::TokenGroup::Error, "Error"},
};

inline const std::string token_group_to_str(core::token::TokenGroup grp) {
  auto it = group_map.find(grp);
  if (it != group_map.end())
    return std::string(it->second);
  return "[UnknownGroup]";
}

} // namespace debug::token