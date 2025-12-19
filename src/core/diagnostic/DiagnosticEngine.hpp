// #pragma once
// #include "parser/error/ParserError.hpp"
// #include <vector>

// namespace core::diagnostics {

// struct DiagnosticsEngine {

//   std::vector<parser::error::ParseError *> errors;

//   // std::vector<Diagnostic> diagnostics;

//   // void print_pointer(std::u32string_view line, size_t start_col, size_t end_col, const std::string &message = "") const {
//   //   std::string ascii_line(line.begin(), line.end());
//   //   if (ascii_line.empty()) ascii_line = " ";

//   //   // imprime a linha original
//   //   debug::Console::log(debug::ColorCode::BrightBlack, "   | ", debug::ColorCode::White, ascii_line);

//   //   // linha de ~
//   //   std::string tildes;
//   //   tildes.resize(start_col - 1, ' ');
//   //   tildes.resize(end_col, '~');
//   //   debug::Console::log(debug::ColorCode::BrightBlack, "   | ", debug::ColorCode::BrightRed, tildes);

//   //   // ponteiro ^ com mensagem
//   //   if (!message.empty()) {
//   //     std::string pointer_line;
//   //     pointer_line.resize(start_col - 1, ' ');
//   //     pointer_line += "^ ";
//   //     debug::Console::log(debug::ColorCode::BrightBlack, "   | ", debug::ColorCode::White, pointer_line, debug::ColorCode::BrightYellow, message);
//   //   }
//   // }

//   // void report(DiagnosticLevel level, const std::string &message, const SourceRange &range, const source::SourceBuffer &buffer, const std::vector<std::string> &hints = {}) {
//   //   diagnostics.push_back({level, message, range, hints});

//   //   std::string level_str;
//   //   switch (level) {
//   //   case DiagnosticLevel::Error: level_str = "error"; break;
//   //   case DiagnosticLevel::Warning: level_str = "warning"; break;
//   //   case DiagnosticLevel::Note: level_str = "note"; break;
//   //   }

//   //   debug::Console::log(debug::ColorCode::Red, level_str, " [", std::to_string(range.begin.line), ":", std::to_string(range.begin.column), "] ", message, "\n");
//   //   for (const auto &hint : hints) { debug::Console::log(debug::ColorCode::Yellow, "  → ", hint, "\n"); }

//   //   auto line = buffer.get_line(range.begin.line);
//   //   print_pointer(line, range.begin.column, range.end.column, message);
//   // }

//   // bool has_errors() const {
//   //   for (const auto &d : diagnostics) {
//   //     if (d.level == DiagnosticLevel::Error) return true;
//   //   }
//   //   return false;
//   // }

//   // // --- imprime todos os diagnostics acumulados ---
//   // void print_all(const source::SourceBuffer &buffer) const {
//   //   for (const auto &d : diagnostics) {
//   //     std::string level_str;
//   //     switch (d.level) {
//   //     case DiagnosticLevel::Error: level_str = "error"; break;
//   //     case DiagnosticLevel::Warning: level_str = "warning"; break;
//   //     case DiagnosticLevel::Note: level_str = "note"; break;
//   //     }

//   //     std::cout << level_str << " [" << d.range.begin.line << ":" << d.range.begin.column << "] " << d.message << "\n";
//   //     for (const auto &hint : d.hints) std::cout << "  → " << hint << "\n";

//   //     auto line = buffer.get_line(d.range.begin.line);
//   //     print_pointer(line, d.range.begin.column, d.range.end.column, d.message);
//   //   }
//   // }

//   // void clear() { diagnostics.clear(); }
// };

// } // namespace core::diagnostics
