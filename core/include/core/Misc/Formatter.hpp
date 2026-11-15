#pragma once

#include <format>

#include "engine/model/IGame/Coords.h"

template <>
struct std::formatter<CoordPair> {
  [[nodiscard]] constexpr auto parse( std::format_parse_context& ctx ) noexcept {
    return ctx.begin();
  }

  [[nodiscard]] auto format( const CoordPair& cp, format_context& ctx ) const noexcept {
    return format_to( ctx.out(), "x={}, y={}", cp.x_, cp.y_ );
  }
};