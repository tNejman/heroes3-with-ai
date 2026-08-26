#pragma once

#include <optional>

#include "Miscellaneous/Coords.h"
class MouseHandler {
 public:
  [[nodiscard]] std::optional<CoordPair> getHexagonCoordsFromClick( int mx, int my ) const noexcept;
  [[nodiscard]] bool pointInHexagon( int px, int py, double hex_x, double hex_y ) const noexcept;
};