#include "WorldMap/OverworldObstacle.h"

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <utility>

#include "Graphics/Visitor.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"

OverworldObstacle::OverworldObstacle( std::string name, CoordPair coords )
    : MapObject( coords ), name_( std::move( name ) ) {
}

sf::Texture& OverworldObstacle::accept( Visitor& v ) const {
  return v.visit( *this );
}

const std::string& OverworldObstacle::getName() const {
  return name_;
}