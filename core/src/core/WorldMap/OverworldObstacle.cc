#include "core/WorldMap/OverworldObstacle.h"

#include <string>
#include <utility>

#include "engine/model/IGraphics/Visitor.h"
#include "core/MapObject/MapObject.h"
#include "engine/model/IGame/Coords.h"

OverworldObstacle::OverworldObstacle( OverworldObstacleType type, CoordPair coords )
    : MapObject( coords ), type_( type ) {
}

void OverworldObstacle::accept( Visitor& v ) const {
  v.visit( *this );
}

OverworldObstacleType OverworldObstacle::getType() const {
  return type_;
}