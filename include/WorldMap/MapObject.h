#pragma once
// Autor: Tomasz Nejman
/*
  - klasa
*/
#include <SFML/Graphics/Texture.hpp>

#include "Graphics/Visitor.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/Printable.h"


class MapObject : public Printable {
 protected:
  CoordPair coords_;

 public:
  MapObject();
  MapObject( CoordPair coords );
  virtual ~MapObject() = default;

  virtual sf::Texture& accept( Visitor& v ) const = 0;
  CoordPair getCoords() const;
  void setCoords( CoordPair new_coords );
};