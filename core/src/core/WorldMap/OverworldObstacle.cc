#include "core/WorldMap/OverworldObstacle.h"

#include <string>
#include <utility>

#include "core/MapObject/MapObject.h"
#include "engine/model/IGame/Coords.h"
#include "engine/model/IGraphics/Visitor.h"

OverworldObstacle::OverworldObstacle( OverworldObstacleType type, CoordPair coords ) noexcept
    : MapObject( coords ), type_( type ) {
}

OverworldObstacleType OverworldObstacle::getType() const noexcept {
  return type_;
}