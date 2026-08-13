#pragma once

#include <format>

#include "Miscellaneous/Coords.h"
template <>
struct std::formatter<CoordPair> {
  constexpr auto parse( std::format_parse_context& ctx ) {
    return ctx.begin();
  }

  auto format( const CoordPair& cp, format_context& ctx ) const {
    return format_to( ctx.out(), "x={}, y={}", cp.x_, cp.y_ );
  }
};