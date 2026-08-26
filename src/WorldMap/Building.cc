#include "WorldMap/Building.h"

#include <string>
#include <utility>

#include "Graphics/Visitor.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"

Building::Building( CoordPair coords, std::string name ) : MapObject( coords ), name_( std::move( name ) ) {
}

void Building::accept( Visitor& v ) const {
  v.visit( *this );
}

std::string Building::getName() const {
  return name_;
}