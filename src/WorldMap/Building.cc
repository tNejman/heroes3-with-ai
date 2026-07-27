#include "WorldMap/Building.h"

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <utility>

#include "Graphics/Visitor.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"

Building::Building( CoordPair coords, std::string name ) : MapObject( coords ), name_( std::move( name ) ) {
}

sf::Texture& Building::accept( Visitor& v ) const {
  return v.visit( *this );
}

std::string Building::getName() const {
  return name_;
}