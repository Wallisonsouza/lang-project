// #pragma once

// #include <cstddef>
// #include <string>
// #include <vector>

// struct State {
//   size_t pos = 0;
//   size_t line = 1;
//   size_t col = 1;
// };

// class TextStream {
// private:
//   const std::u32string &source;
//   const char32_t *ptr;
//   const char32_t *end;

//   State current;
//   std::vector<State> checkpoints;

// public:
//   explicit TextStream(std::u32string &src) : source(src), ptr(src.data()), end(src.data() + src.size()), current{0, 1, 1} {}

//   const State &get_state() { return current; }

//   void advance(size_t count = 1) {
//     for (size_t i = 0; i < count && ptr < end; ++i) {
//       char32_t c = *ptr++;
//       current.pos++;
//       if (c == U'\n') {
//         current.line++;
//         current.col = 1;
//       } else {
//         current.col++;
//       }
//     }
//   }

//   char32_t peek(size_t offset = 0) const {
//     const char32_t *p = ptr + offset;
//     return p < end ? *p : U'\0';
//   }

//   bool eof() const { return ptr >= end; }

//   size_t current_position() const { return current.pos; }
//   size_t line() const { return current.line; }
//   size_t current_column() const { return current.col; }

//   State push() {
//     checkpoints.push_back(current);
//     return current;
//   }

//   void pop_restore() {
//     if (checkpoints.empty()) return;
//     current = checkpoints.back();
//     checkpoints.pop_back();
//     ptr = source.data() + current.pos;
//   }

//   void pop_discard() {
//     if (!checkpoints.empty()) checkpoints.pop_back();
//   }

//   void reset(size_t new_pos) {
//     current = {0, 1, 1};
//     ptr = source.data();
//     advance(new_pos);
//   }
// };
