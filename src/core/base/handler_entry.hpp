#pragma once
#include "core/base/handler_base.hpp"

struct HandlerEntry {
  int priority;
  std::unique_ptr<HandlerBase> handler;
};
