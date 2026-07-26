#include "WorldMap/OverworldObstacle.h"

OverworldObstacle::OverworldObstacle( const std::string& name, CoordPair coords )
    : MapObject( coords ), name_( name ) {}

sf::Texture& OverworldObstacle::accept( Visitor& v ) const {
  return v.visit( *this );
}

const std::string& OverworldObstacle::getName() const {
  return name_;
}