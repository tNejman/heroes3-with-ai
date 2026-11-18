#include "core/WorldMap/Building.h"

#include <string>
#include <utility>

#include "engine/model/IGame/Coords.h"

#include "core/MapObject/MapObject.h"

Building::Building( CoordPair coords, std::string name ) : MapObject( coords ), name_( std::move( name ) ) {
}

std::string Building::getName() const {
  return name_;
}