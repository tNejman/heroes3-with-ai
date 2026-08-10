#include "MapObject/MapObject.h"

#include "Miscellaneous/Coords.h"

MapObject::MapObject( CoordPair coords ) : coords_( coords ) {};

CoordPair MapObject::getCoords() const {
  return coords_;
}
void MapObject::setCoords( CoordPair new_coords ) {
  coords_ = new_coords;
}

Character* MapObject::asCharacter() noexcept {
  return nullptr;
}