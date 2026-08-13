#pragma once
// Autor: Tomasz Nejman
/*
  - klasa
*/
#include <SFML/Graphics/Texture.hpp>

#include "Graphics/Printable.h"
#include "Graphics/Visitor.h"
#include "Miscellaneous/Coords.h"

class Character;

class MapObject : public Printable {
 protected:
  CoordPair coords_;
  bool is_traversable_;

 public:
  MapObject( CoordPair coords );
  MapObject( CoordPair coords, bool is_traversable );
  virtual ~MapObject() = default;

  sf::Texture& accept( Visitor& v ) const override = 0;
  [[nodiscard]] CoordPair getCoords() const noexcept;
  void setCoords( CoordPair new_coords ) noexcept;
  [[nodiscard]] bool isTraversable() const noexcept;

  [[nodiscard]] virtual Character* asCharacter() noexcept;
};