
#include "IO/MouseHandler.h"

#include <cmath>
#include <optional>

#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

[[nodiscard]] std::optional<CoordPair> MouseHandler::getHexagonCoordsFromClick( int mx, int my ) const noexcept {
  if ( mx < 0 || my < 0 ) {
    return std::nullopt;
  }

  for ( int x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( int y = 0; y < MAP_HEIGHT_BF; ++y ) {
      int offset_x_temp = BATTLE_MAP_SPRITE_INITIAL_OFFSET_X_ODD + ( x * BATTLE_MAP_SPRITE_X_DELTA );
      int offset_y_temp = BATTLE_MAP_SPRITE_INITIAL_OFFSET_Y_ODD + ( ( 5 - ( y / 2 ) ) * BATTLE_MAP_SPRITE_Y_DELTA );

      // adjust if even
      if ( ( y % 2 == 0 ) ) {
        offset_x_temp += BATTLE_MAP_SPRITE_ADJUST_EVEN_X;
        offset_y_temp += BATTLE_MAP_SPRITE_ADJUST_EVEN_Y;
      }
      double hex_center_x = double( offset_x_temp ) + ( HEXAGON_SPRITE_WIDTH / 2.0 );
      double hex_center_y = double( offset_y_temp ) + ( HEXAGON_SPRITE_HEIGHT / 2.0 );

      if ( pointInHexagon( mx, my, hex_center_x, hex_center_y ) ) {
        return CoordPair( x, y );
      }
    }
  }
  return std::nullopt;
}

bool MouseHandler::pointInHexagon( int px, int py, double hex_x, double hex_y ) const noexcept {
  double dx = std::abs( px - hex_x );
  double dy = std::abs( py - hex_y );

  double dx_squared = dx * dx;
  double dy_squared = dy * dy;

  double distance_diagonal = std::sqrt( dx_squared + dy_squared );

  return distance_diagonal <= HEXAGON_SPRITE_MAX_RADIUS;
}