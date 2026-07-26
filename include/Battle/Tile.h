#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Tile:
  - Klasa Tile odpowiada za pojedynczy kafelek na polu bitwy.
  - Kafelek może zawierać obiekt, który jest na nim umieszczony oraz sąsiadujące kafelki.
*/

#include "Battle/TileObject.h"
#include "Miscellaneous/Coords.h"

class Tile {
 private:
  std::shared_ptr<TileObject> tileObject_;
  const CoordPair coords_;

 public:
  Tile( std::shared_ptr<TileObject> tile_object, const CoordPair coords ) : tileObject_( tile_object ), coords_( coords ) {};
  Tile( const CoordPair coords ) : tileObject_( nullptr ), coords_( coords ) {};
  const CoordPair& getCoords() const;
  //  Tile(std::string name, const CoordPair coords) : tileObject_(), coords_(coords) {};
  //  void setNeighbour( directions n, std::shared_ptr<Tile> neigbour );
  //  std::shared_ptr<Tile> getNeighbour( int neighbour );
  //  std::vector<std::shared_ptr<Tile>> getNeighbour();
  //  std::vector<std::shared_ptr<Tile>> getSurrounding( int x, int y, int range );
  void setObject( std::shared_ptr<TileObject> new_tile_object );
  std::shared_ptr<TileObject> getObject();
  Tile copy();
  ~Tile() {};
};