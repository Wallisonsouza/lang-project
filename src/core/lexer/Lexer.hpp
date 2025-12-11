#pragma once
#include "core/LangData.hpp"
#include "core/lexer/plugin.hpp"
#include <memory>
#include <vector>

struct PluginEntry {
  std::shared_ptr<interpreter::lexer::LexerPlugin> plugin;
  int priority;
};

namespace interpreter::lexer {
class Lexer {

private:
  std::vector<PluginEntry> plugins;
  core::LangData &data;

public:
  Lexer(core::LangData &data) : data(data) {}

  void add_plugin(std::shared_ptr<LexerPlugin> p, int priority = 0) {
    plugins.emplace_back(PluginEntry{p, priority});
    std::sort(plugins.begin(), plugins.end(), [](const auto &a, const auto &b) { return a.priority < b.priority; });
  }

  bool try_plugin(TextStream &stream, LexerPlugin &plugin) {
    stream.push_checkpoint();
    if (plugin.match(stream, data)) {
      stream.discard_checkpoint();
      return true;
    } else {
      stream.rollback_checkpoint();
      return false;
    }
  }

  void generate_tokens() {
    TextStream stream(data.buffer);

    while (!stream.eof()) {
      bool matched = false;

      for (auto &entry : plugins) {
        if (try_plugin(stream, *entry.plugin)) {
          matched = true;
          break;
        }
      }

      if (!matched) { stream.advance(); }
    }
  }
};

} // namespace interpreter::lexer
