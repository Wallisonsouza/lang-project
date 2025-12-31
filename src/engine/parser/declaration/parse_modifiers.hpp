#pragma once
#include "core/node/Modifier.hpp"
#include "core/token/token_stream.hpp"

namespace parser::declaration {

core::node::Modifiers parse_modifiers(core::token::TokenStream &stream);

}
