#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Tile:
  - Klasa Tile odpowiada za pojedynczy kafelek na polu bitwy.
  - Kafelek może zawierać obiekt, który jest na nim umieszczony oraz sąsiadujące kafelki.
*/

#include <memory>
#include <utility>

#include "Battle/TileObject.hpp"
#include "Miscellaneous/Coords.h"

class TileObject;

class Tile {
 private:
  TileObject* tile_object_;
  CoordPair coords_;

 public:
  Tile( TileObject* tile_object, CoordPair coords ) : tile_object_( tile_object ), coords_( coords ) {};
  Tile( CoordPair coords ) : tile_object_( nullptr ), coords_( coords ) {};
  [[nodiscard]] CoordPair getCoords() const;
  //  Tile(std::string name, const CoordPair coords) : tileObject_(), coords_(coords) {};
  //  void setNeighbour( directions n, std::shared_ptr<Tile> neigbour );
  //  std::shared_ptr<Tile> getNeighbour( int neighbour );
  //  std::vector<std::shared_ptr<Tile>> getNeighbour();
  //  std::vector<std::shared_ptr<Tile>> getSurrounding( int x, int y, int range );
  void setObject( TileObject& new_tile_object );
  void resetObject() noexcept;
  TileObject* getObject();
  Tile copy();
};