#pragma once
#include <stdexcept>
#include <string>

class StackException : public std::runtime_error {
public:
  explicit StackException(const std::string &msg) : std::runtime_error(msg) {}
};

class StackRestoreException : public StackException {
public:
  StackRestoreException()
      : StackException("No saved positions to restore in stack") {}
};

class StackRetreatException : public StackException {
public:
  StackRetreatException() : StackException("Already at beginning of stack") {}
};
