#pragma once
#include "core/plugin/Plugin.hpp"
#include <functional>
#include <memory>
#include <vector>

namespace lang::core {

class PluginRegistry {
private:
  struct OrderedPlugin {
    std::shared_ptr<Plugin> plugin;
    int order;
  };

  std::vector<OrderedPlugin> plugins;

public:
  void add(std::shared_ptr<Plugin> plugin, int order = 100);
  void for_each(const std::function<void(Plugin &)> &fn);
  std::vector<std::shared_ptr<Plugin>> get_all() const;
};

} // namespace lang::core
