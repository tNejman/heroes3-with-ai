#pragma once
// Autor: Tomasz Nejman
/*
  - klasa
*/
#include "Miscellaneous/Printable.h"
#include "Miscellaneous/ProjectLib.h"

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