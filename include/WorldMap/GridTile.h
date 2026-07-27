#pragma once
// Autor: Tomasz Naszkowski

// #include <SFML/Graphics.hpp>

#include <memory>

#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

// #include "Characters/Character.h"
#include "MapObject/MapObject.h"

class Character;

class GridTile {
 private:
  CoordPair coords_;
  Terrain terrain_;
  std::shared_ptr<MapObject> object_present_ = nullptr;

 public:
  GridTile( CoordPair coords, Terrain terrain );
  GridTile( CoordPair coords, Terrain terrain, std::shared_ptr<MapObject> object );

  [[nodiscard]] CoordPair getCoords() const;

  [[nodiscard]] Terrain getTerrain();
  void setTerrain( Terrain new_terrain );

  [[nodiscard]] std::shared_ptr<MapObject> getMapObject();
  void setMapObject( std::shared_ptr<MapObject> new_object );
  void deleteObject();

  [[nodiscard]] bool isTraversable() const noexcept;
};