#pragma once
#include "core/base/handler_base.hpp"
#include "core/base/handler_entry.hpp"
#include <memory>
#include <vector>

class HandlerContext {
public:
  HandlerContext() = default;

  void addHandler(int priority, std::unique_ptr<HandlerBase> handler);
  const std::vector<HandlerEntry> &getHandlers() const;

private:
  std::vector<HandlerEntry> handlers;
};
