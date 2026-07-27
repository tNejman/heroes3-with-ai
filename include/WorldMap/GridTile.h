#pragma once
// Autor: Tomasz Naszkowski

// #include <SFML/Graphics.hpp>

#include <memory>

#include "Miscellaneous/ProjectLib.h"

// #include "Characters/Character.h"
#include "MapObject/MapObject.h"

class Character;

class GridTile {
 private:
  uint32_t x_coord_;
  uint32_t y_coord_;
  Terrain terrain_;
  std::shared_ptr<MapObject> object_present_ = nullptr;

 public:
  GridTile( Terrain terrain ) : terrain_( terrain ) {};
  GridTile( Terrain terrain, CoordPair coords ) : terrain_( terrain ) {
    x_coord_ = coords.x_;
    y_coord_ = coords.y_;
  }
  GridTile( Terrain terrain, std::shared_ptr<MapObject> object, CoordPair coords ) : terrain_( terrain ) {
    x_coord_ = coords.x_;
    y_coord_ = coords.y_;
    object_present_ = std::move( object );
  }

  CoordPair getCoords() const;

  Terrain getTerrain();
  void setTerrain( Terrain new_terrain );

  const std::shared_ptr<MapObject> getMapObject();
  void setMapObject( std::shared_ptr<MapObject> new_object );
  void deleteObject();

  bool getIfTraversable();
};