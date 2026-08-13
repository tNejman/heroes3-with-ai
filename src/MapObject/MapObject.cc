#include "MapObject/MapObject.h"

#include <SFML/Graphics/Texture.hpp>

#include "Miscellaneous/Coords.h"

MapObject::MapObject( CoordPair coords ) : coords_( coords ), is_traversable_( false ) {};

MapObject::MapObject( CoordPair coords, bool is_traversable ) : coords_( coords ), is_traversable_( is_traversable ) {};

CoordPair MapObject::getCoords() const noexcept {
  return coords_;
}
void MapObject::setCoords( CoordPair new_coords ) noexcept {
  coords_ = new_coords;
}

[[nodiscard]] bool MapObject::isTraversable() const noexcept {
  return is_traversable_;
}

[[nodiscard]] Character* MapObject::asCharacter() noexcept {
  return nullptr;
}
