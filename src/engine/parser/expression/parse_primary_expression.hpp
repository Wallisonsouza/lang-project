#pragma once

#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"

namespace parser::expression {

core::node::ExpressionNode *parse_primary_expression(CompilationUnit &unit, core::token::TokenStream &stream);

}
