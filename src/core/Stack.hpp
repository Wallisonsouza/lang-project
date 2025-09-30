#pragma once
#include <cstddef>
#include <vector>

class Stack {
public:
  Stack();

  void save();
  void restore();

  std::size_t getPosition() const;
  void advance();
  void retreat();

private:
  std::vector<std::size_t> stack;
  std::size_t current;
};