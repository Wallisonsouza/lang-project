// #pragma once
// #include <cstddef>
// #include <iostream>
// #include <memory>
// #include <vector>

// template <typename T> class Stream {
// private:
//   std::shared_ptr<std::vector<T>> content;
//   size_t cursor = 0;
//   std::vector<size_t> savedPositions;

// public:
//   explicit Stream(std::shared_ptr<std::vector<T>> vec) :
//   content(std::move(vec)), cursor(0) {}

//   void setContent(std::shared_ptr<std::vector<T>> vec) {
//     content = std::move(vec);
//     cursor  = 0;
//     savedPositions.clear();
//   }

//   void print() const {
//     if (!content)
//       return;
//     for (const auto &c : *content)
//       std::cout << c << ' ';
//     std::cout << "\n";
//   }

//   bool has_next() const { return content && cursor < content->size(); }
//   bool isEnd() const { return !has_next(); }

//   const T *current() const {
//     if (!has_next())
//       return nullptr;
//     return &(*content)[cursor];
//   }

//   const T *advance() {
//     if (!has_next())
//       return nullptr;
//     return &(*content)[cursor++];
//   }

//   const T *peek(size_t ahead = 1) const {
//     if (!content)
//       return nullptr;
//     size_t pos = cursor + ahead - 1;
//     if (pos >= content->size())
//       return nullptr;
//     return &(*content)[pos];
//   }

//   void retreat(size_t steps = 1) {
//     if (steps > cursor)
//       cursor = 0;
//     else
//       cursor -= steps;
//   }

//   size_t get_position() const { return cursor; }
//   void reset() { cursor = 0; }
//   size_t size() const { return content ? content->size() : 0; }

//   const T *operator[](size_t i) const {
//     if (!content || i >= content->size())
//       return nullptr;
//     return &(*content)[i];
//   }

//   void save() { savedPositions.push_back(cursor); }

//   void rollback() {
//     if (!savedPositions.empty()) {
//       cursor = savedPositions.back();
//       savedPositions.pop_back();
//     }
//   }
// };
