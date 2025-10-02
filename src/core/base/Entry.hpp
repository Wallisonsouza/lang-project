#pragma once
#include <memory>

template <typename T> struct Entry {
  int priority;
  std::unique_ptr<T> plugin;
};
