// #pragma once
// #include "core/utils/Utf8.hpp"
// #include <fstream>
// #include <sstream>
// #include <stdexcept>
// #include <string>
// #include <utility>

// struct TokenHash {
//   const TextBuffer *buffer;
//   explicit TokenHash(const TextBuffer *buf) : buffer(buf) {}

//   size_t operator()(const TextSpan &span) const noexcept { return buffer->hash_span(span); }
// };

// struct TokenEqual {
//   const TextBuffer *buffer;
//   explicit TokenEqual(const TextBuffer *buf) : buffer(buf) {}

//   bool operator()(const TextSpan &a, const TextSpan &b) const noexcept { return buffer->equal_span(a, b); }
// };

// #include "core/utils/TextBuffer.hpp"
// #include "core/utils/Utf8.hpp"
// #include <string>

// class TextStream {
// public:
//   const char32_t *begin = nullptr;
//   const char32_t *current = nullptr;
//   const char32_t *end = nullptr;

//   size_t line = 1;
//   size_t column = 1;

//   TextStream() = default;

//   explicit TextStream(const TextBuffer *buffer) { set_buffer(buffer); }

//   void set_buffer(const TextBuffer *buffer) {
//     begin = buffer->u32().data();
//     current = begin;
//     end = begin + buffer->u32_size();

//     line = 1;
//     column = 1;
//   }

//   bool eof() const { return current >= end; }

//   char32_t peek() const { return eof() ? U'\0' : *current; }

//   char32_t peek_next() const { return (current + 1 >= end) ? U'\0' : *(current + 1); }

//   char32_t advance() {
//     if (eof()) return U'\0';

//     char32_t c = *current++;

//     if (c == U'\n') {
//       line++;
//       column = 1;
//     } else {
//       column++;
//     }

//     return c;
//   }

//   bool match(char32_t c) {
//     if (peek() == c) {
//       advance();
//       return true;
//     }
//     return false;
//   }

//   const char32_t *mark() const { return current; }

//   std::string slice_utf8(const char32_t *s, const char32_t *e) const {
//     std::string out;
//     out.reserve((e - s) * 4);
//     for (auto p = s; p < e; ++p) interpreter::utils::Utf8::encode(*p, out);
//     return out;
//   }
// };
