#include "core/context/handler_context.hpp"
#include <algorithm>

void HandlerContext::addHandler(int priority, std::unique_ptr<HandlerBase> handler) {
  handlers.push_back({priority, std::move(handler)});
  std::sort(handlers.begin(), handlers.end(), [](const HandlerEntry &a, const HandlerEntry &b) { return a.priority < b.priority; });
}

const std::vector<HandlerEntry> &HandlerContext::getHandlers() const { return handlers; }
