#include "core/WorldMap/Building.h"

#include <string>
#include <utility>

#include "engine/Graphics/Visitor.h"
#include "core/MapObject/MapObject.h"
#include "engine/IGame/Coords.h"

Building::Building( CoordPair coords, std::string name ) : MapObject( coords ), name_( std::move( name ) ) {
}

void Building::accept( Visitor& v ) const {
  v.visit( *this );
}

std::string Building::getName() const {
  return name_;
}