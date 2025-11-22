#include "core/plugin/Matcher.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace lang::core {
struct LangData;
}

namespace lang::core {
class MatcherManager {
private:
  std::vector<std::unique_ptr<lang::core::Matcher>> matchers;

public:
  void add(std::unique_ptr<Matcher> m) {
    matchers.push_back(std::move(m));
    std::sort(matchers.begin(), matchers.end(), [](auto &a, auto &b) { return a->priority > b->priority; });
  }

  std::shared_ptr<Token> run(Stream<char32_t> &stream, LangData &data) {
    for (auto &m : matchers) {
      auto t = m->match(stream, data);
      if (t)
        return t;
    }
    return nullptr;
  }
};
} // namespace lang::core
