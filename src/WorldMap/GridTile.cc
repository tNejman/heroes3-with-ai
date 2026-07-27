#include "WorldMap/GridTile.h"

#include <cstddef>
#include <memory>
#include <utility>

#include "Exceptions/_NotImplementedException.hpp"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

GridTile::GridTile( CoordPair coords, Terrain terrain ) : coords_( coords ), terrain_( terrain ) {
}

GridTile::GridTile( CoordPair coords, Terrain terrain, std::shared_ptr<MapObject> object )
    : coords_( coords ), terrain_( terrain ), object_present_( std::move( object ) ) {
}

Terrain GridTile::getTerrain() {
  return this->terrain_;
}

void GridTile::setTerrain( Terrain new_terrain ) {
  this->terrain_ = new_terrain;
}

CoordPair GridTile::getCoords() const {
  return this->coords_;
}

std::shared_ptr<MapObject> GridTile::getMapObject() {
  return this->object_present_;
}

void GridTile::setMapObject( std::shared_ptr<MapObject> new_object ) {
  this->object_present_ = std::move( new_object );
}

void GridTile::deleteObject() {
  this->object_present_.reset();
}

bool GridTile::isTraversable() const noexcept {
  return object_present_ == nullptr;
}