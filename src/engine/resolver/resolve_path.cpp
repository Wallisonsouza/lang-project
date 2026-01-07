#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_path(parser::node::statement::PathExprNode *path) {

  SymbolId sym = INVALID_SYMBOL_ID;

  std::cout << "[resolve_path] Resolving path: ";
  for (const auto &s : path->segments) std::cout << s->name << "::";
  std::cout << "\n";

  for (size_t i = 0; i < path->segments.size(); ++i) {
    auto *seg = path->segments[i];
    std::cout << "[resolve_path] Segment: " << seg->name << "\n";

    if (i == path->segments.size() - 1) {
      sym = current_scope->find(seg->name);
      if (sym != INVALID_SYMBOL_ID) {
        std::cout << "[resolve_path] Found symbol '" << seg->name << "'\n";
      } else {
        std::cout << "[resolve_path] Symbol '" << seg->name << "' not founda!\n";
        // Aqui você pode emitir um erro no CompilationUnit
        // unit.diagnostics.emit({DiagnosticCode::UndeclaredSymbol, seg->slice});
      }
    } else {
      auto it = current_scope->imports.find(seg->name);
      if (it == current_scope->imports.end()) {
        std::cout << "[resolve_path] Module '" << seg->name << "' not found!\n";
        return;
      }
      std::cout << "[resolve_path] Found module '" << seg->name << "'\n";
      current_scope = it->second;
    }
  }

  if (sym == INVALID_SYMBOL_ID) { std::cout << "invalid"; }

  path->symbol_id = sym;
}
