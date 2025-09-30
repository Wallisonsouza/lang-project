#include "Stack.hpp"
#include "errors/StackErrors.hpp"

Stack::Stack() : current(0) {}

void Stack::save() { stack.push_back(current); }

void Stack::restore() {
  if (stack.empty()) {
    throw StackRestoreException();
  }

  current = stack.back();
  stack.pop_back();
}

size_t Stack::getPosition() const { return current; }

void Stack::advance() { current++; }

void Stack::retreat() {
  if (current == 0) {
    throw StackRetreatException();
  }

  current--;
}