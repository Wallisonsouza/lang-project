// #pragma once
// #include "core/CompilationUnit.hpp"
// #include "core/module/Scope.hpp"
// #include "utils/Utf8.hpp"
// #include <iostream>

// namespace semantic {

// inline void validate_variable_declaration(CompilationUnit &unit, parser::VariableDeclarationNode *var, core::Scope &scope) {

//   // // --- Resolver tipo ---
//   // if (!var->type || var->type->has_error) {
//   //   std::cerr << "Missing or invalid type for variable: " << std::string(var->name.begin(), var->name.end()) << "\n";
//   //   has_error = true;
//   // } else {
//   //   // Se for genérico, validar cada argumento
//   //   for (auto &gen_arg : var->type->generics) {
//   //     if (!gen_arg || gen_arg->has_error) {
//   //       std::cerr << "Invalid generic type argument in variable: " << std::string(var->name.begin(), var->name.end()) << "\n";
//   //       gen_arg->has_error = true;
//   //       has_error = true;
//   //     } else {
//   //       auto type_node = scope.find_type(gen_arg->name);
//   //       if (!type_node) {
//   //         std::cerr << "Unknown generic type: " << utils::Utf::utf32to8(gen_arg->name) << "\n";
//   //         gen_arg->has_error = true;
//   //         has_error = true;
//   //       } else {
//   //         gen_arg = type_node;
//   //       }
//   //     }
//   //   }

//   //   // Resolver tipo principal
//   //   auto type_node = scope.find_type(var->type->name);
//   //   if (!type_node) {
//   //     std::cerr << "Unknown type: " << utils::Utf::utf32to8(var->type->name) << "\n";
//   //     var->type->has_error = true;
//   //     has_error = true;
//   //   } else {
//   //     var->type = type_node;
//   //   }
//   // }

//   // // --- Resolver valor ---
//   // if (var->value) {
//   //   if (auto ident = dynamic_cast<parser::IdentifierNode *>(var->value)) {
//   //     auto decl = scope.find_variable(ident->name);
//   //     if (!decl) {
//   //       std::cerr << "Unknown variable: " << std::string(ident->name.begin(), ident->name.end()) << "\n";
//   //       ident->has_error = true;
//   //       has_error = true;
//   //     } else {
//   //       // Opcional: link para a declaração
//   //       // ident->declaration = decl;
//   //     }
//   //   }
//   // }

//   // // --- Registrar variável no escopo ---
//   // if (!scope.has_variable_in_current_scope(var->name)) {
//   //   scope.add_variable(var->name, var);
//   // } else {
//   //   std::cerr << "Variable already declared: " << std::string(var->name.begin(), var->name.end()) << "\n";
//   //   has_error = true;
//   // }

//   // var->has_error = has_error;
// }

// } // namespace semantic
