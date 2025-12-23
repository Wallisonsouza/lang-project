#pragma once

#include "debug/console/color.hpp"

namespace debug::node {

inline const Color entry_color = Color(200, 200, 200);     // cinza claro
inline const Color typeColor = Color(102, 153, 255);       // azul pastel
inline const Color valueColor = Color(255, 153, 102);      // laranja pastel
inline const Color funcColor = Color(153, 255, 153);       // verde claro
inline const Color paramColor = Color(255, 204, 204);      // rosa suave
inline const Color operatorColor = Color(255, 204, 102);   // amarelo suave
inline const Color numberColor = Color(153, 204, 255);     // azul claro
inline const Color stringColor = Color(204, 153, 255);     // lilás pastel
inline const Color voidColor = Color(192, 192, 192);       // cinza neutro
inline const Color identifierColor = Color(255, 255, 153); // amarelo claro

} // namespace debug::node
