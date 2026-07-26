#include "WorldMap/GridTile.h"

Terrain GridTile::getTerrain() {
  return this->terrain_;
}

const std::shared_ptr<MapObject> GridTile::getMapObject() {
  return this->object_present_;
}

void GridTile::setMapObject( std::shared_ptr<MapObject> new_object ) {
  this->deleteObject();
  this->object_present_ = new_object;
}

void GridTile::deleteObject() {
  this->object_present_.reset();
}
