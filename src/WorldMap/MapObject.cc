#include "WorldMap/MapObject.h"

MapObject::MapObject()
    : coords_( CoordPair( 0u, 0u ) ) {};

MapObject::MapObject( CoordPair coords )
    : coords_( coords ) {};

CoordPair MapObject::getCoords() const {
  return coords_;
}
void MapObject::setCoords( CoordPair new_coords ) {
  coords_ = new_coords;
}