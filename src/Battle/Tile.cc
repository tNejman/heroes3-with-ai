#include "Battle/Tile.h"

#include "Miscellaneous/Coords.h"


const CoordPair& Tile::getCoords() const {
  return this->coords_;
}

// void Tile::setNeighbour( directions n, std::shared_ptr<Tile> neigbour ) {
//   neighbours_[(int)n] = neigbour;
// }
// std::shared_ptr<Tile> Tile::getNeighbour( int neighbour ) {
//   return neighbours_[neighbour];
// }

// std::vector<std::shared_ptr<Tile>> Tile::getNeighbour() {
//   std::vector<std::shared_ptr<Tile>> tmp;
//   for(auto& neighbour: neighbours_){
//     tmp.push_back(neighbour);
//   }
//   return tmp;
// }

void Tile::setObject( std::shared_ptr<TileObject> new_tile_object ) {
  tile_object_ = new_tile_object;
}

std::shared_ptr<TileObject> Tile::getObject() {
  return tile_object_;
}

Tile Tile::copy() {
  return Tile( tile_object_, coords_ );
}
// void Tile::resetNeighbours() {
//   for (auto& n : neighbours_) {
//     n.reset();
//   }
// }