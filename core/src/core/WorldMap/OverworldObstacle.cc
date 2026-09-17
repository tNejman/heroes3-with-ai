#include "core/WorldMap/OverworldObstacle.h"

#include <string>
#include <utility>

#include "engine/Graphics/Visitor.h"
#include "core/MapObject/MapObject.h"
#include "core/Misc/Coords.h"

OverworldObstacle::OverworldObstacle( OverworldObstacleType type, CoordPair coords )
    : MapObject( coords ), type_( type ) {
}

void OverworldObstacle::accept( Visitor& v ) const {
  v.visit( *this );
}

OverworldObstacleType OverworldObstacle::getType() const {
  return type_;
}