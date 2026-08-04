#include "Battle/Tile.h"

#include <memory>
#include <utility>

#include "Miscellaneous/Coords.h"

CoordPair Tile::getCoords() const {
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

void Tile::setObject( TileObject& new_tile_object ) {
  tile_object_ = &new_tile_object;
}

TileObject* Tile::getObject() {
  return tile_object_;
}

Tile Tile::copy() {
  if ( tile_object_ == nullptr ) {
    return Tile{ nullptr, coords_ };
  }
  return { tile_object_, coords_ };
}

void Tile::resetObject() noexcept {
  tile_object_ = nullptr;
}

// void Tile::resetNeighbours() {
//   for (auto& n : neighbours_) {
//     n.reset();
//   }
// }