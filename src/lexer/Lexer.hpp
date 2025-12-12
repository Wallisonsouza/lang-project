#pragma once
#include "lexer/plugin.hpp"
#include <memory>
#include <vector>

struct PluginEntry {
  std::shared_ptr<lexer::LexerPlugin> plugin;
  int priority;
};

namespace lexer {
class Lexer {

private:
  std::vector<PluginEntry> plugins;
  core::LangData &data;

public:
  Lexer(core::LangData &data) : data(data) {}

  void add_plugin(std::shared_ptr<lexer::LexerPlugin> p, int priority = 0) {
    plugins.emplace_back(PluginEntry{p, priority});
    std::sort(plugins.begin(), plugins.end(), [](const auto &a, const auto &b) {
      return a.priority < b.priority;
    });
  }

  bool try_plugin(core::text::TextStream &stream, lexer::LexerPlugin &plugin) {

    stream.push_checkpoint();
    auto tok = plugin.match(stream, data);

    if (tok) {
      stream.discard_checkpoint();
      data.tokens_storage.push_back(*tok);
      return true;
    }

    stream.rollback_checkpoint();
    return false;
  }

  void generate_tokens() {
    core::text::TextStream stream(data.buffer);

    while (!stream.eof()) {
      bool matched = false;

      for (auto &entry : plugins) {
        if (try_plugin(stream, *entry.plugin)) {
          matched = true;
          break;
        }
      }

      if (!matched) {
        stream.advance();
      }
    }
  }
};

} // namespace lexer
