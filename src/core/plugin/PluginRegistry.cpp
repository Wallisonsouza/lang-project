#include "PluginRegistry.hpp"
#include <algorithm>

namespace lang::core {

void PluginRegistry::add(std::shared_ptr<Plugin> plugin, int order) {
  plugins.push_back({std::move(plugin), order});

  std::sort(plugins.begin(), plugins.end(), [](const OrderedPlugin &a, const OrderedPlugin &b) { return a.order < b.order; });
}

void PluginRegistry::for_each(const std::function<void(Plugin &)> &fn) {
  for (auto &entry : plugins) {
    if (entry.plugin)
      fn(*entry.plugin);
  }
}

std::vector<std::shared_ptr<Plugin>> PluginRegistry::get_all() const {
  std::vector<std::shared_ptr<Plugin>> result;
  result.reserve(plugins.size());
  for (const auto &entry : plugins)
    result.push_back(entry.plugin);
  return result;
}

} // namespace lang::core
