#pragma once

#include <string>

#include "engine/model/IGame/Coords.h"

inline std::string toString( const CoordPair& cp ) {
  return "x=" + std::to_string( cp.x_ ) + ", y=" + std::to_string( cp.y_ );
}
