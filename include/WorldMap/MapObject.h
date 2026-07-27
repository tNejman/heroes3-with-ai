#pragma once
// Autor: Tomasz Nejman
/*
  - klasa
*/
#include <SFML/Graphics/Texture.hpp>

#include "Graphics/Printable.h"
#include "Graphics/Visitor.h"
#include "Miscellaneous/Coords.h"


class MapObject : public Printable {
 protected:
  CoordPair coords_;

 public:
  MapObject();
  MapObject( CoordPair coords );

  sf::Texture& accept( Visitor& v ) const override = 0;
  [[nodiscard]] CoordPair getCoords() const;
  void setCoords( CoordPair new_coords );
};