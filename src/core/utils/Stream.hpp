// #pragma once
// #include <cstddef>
// #include <stack>
// #include <vector>

// namespace lang::utils {

// template <typename T> class Stream {
// private:
//   std::vector<T> &source;
//   std::size_t index = 0;
//   std::stack<std::size_t> saved;

// public:
//   explicit Stream(std::vector<T> &src) : source(src) {}

//   T *current() {
//     if (index == 0 || index > source.size())
//       return nullptr;
//     return &source[index - 1];
//   }

//   T *peek(std::size_t offset = 0) {
//     if (index + offset >= source.size())
//       return nullptr;
//     return &source[index + offset];
//   }

//   T *advance() {
//     if (index >= source.size())
//       return nullptr;
//     return &source[index++];
//   }

//   bool has_next() const noexcept { return index < source.size(); }

//   void save() { saved.push(index); }

//   void restore() {
//     if (!saved.empty()) {
//       index = saved.top();
//       saved.pop();
//     }
//   }

//   void discard() {
//     if (!saved.empty())
//       saved.pop();
//   }

//   std::size_t position() const noexcept { return index; }

//   std::vector<T> &get_source() noexcept { return source; }
// };

// } // namespace lang::utils
