#pragma once
// Autor: Tomasz Nejman
/*
  - klasa
*/

#include "engine/Graphics/IPrintable.h"
#include "engine/Graphics/Visitor.h"
#include "core/Misc/Coords.h"

class Character;

class MapObject : public IPrintable {
 protected:
  CoordPair coords_;
  bool is_traversable_;

 public:
  MapObject( CoordPair coords );
  MapObject( CoordPair coords, bool is_traversable );
  virtual ~MapObject() = default;

  void accept( Visitor& v ) const override = 0;
  [[nodiscard]] CoordPair getCoords() const noexcept;
  void setCoords( CoordPair new_coords ) noexcept;
  [[nodiscard]] bool isTraversable() const noexcept;

  [[nodiscard]] virtual Character* asCharacter() noexcept;
};