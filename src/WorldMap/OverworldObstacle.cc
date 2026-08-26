#include "WorldMap/OverworldObstacle.h"

#include <string>
#include <utility>

#include "Graphics/Visitor.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"

OverworldObstacle::OverworldObstacle( OverworldObstacleType type, CoordPair coords )
    : MapObject( coords ), type_( type ) {
}

void OverworldObstacle::accept( Visitor& v ) const {
  v.visit( *this );
}

OverworldObstacleType OverworldObstacle::getType() const {
  return type_;
}