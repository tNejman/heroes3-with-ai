#pragma once
// Autor: Tomasz Nejman
/*
  - klasa
*/

#include "engine/model/IGame/Coords.h"
#include "engine/model/IGraphics/IPrintable.h"
#include "engine/model/IGraphics/Visitor.h"

class Character;

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
class MapObject : public IPrintable {
 protected:
  CoordPair coords_;     // NOLINT(misc-non-private-member-variables-in-classes,
                         // cppcoreguidelines-non-private-member-variables-in-classes)
  bool is_traversable_;  // NOLINT(misc-non-private-member-variables-in-classes,
                         // cppcoreguidelines-non-private-member-variables-in-classes)

 public:
  [[nodiscard]] MapObject( CoordPair coords ) noexcept;
  [[nodiscard]] MapObject( CoordPair coords, bool is_traversable ) noexcept;
  virtual ~MapObject() = default;  // NOLINT(modernize-use-override, cppcoreguidelines-explicit-virtual-functions)

  [[nodiscard]] CoordPair getCoords() const noexcept;
  void setCoords( CoordPair new_coords ) noexcept;
  [[nodiscard]] bool isTraversable() const noexcept;

  [[nodiscard]] virtual const Character* asCharacter() const noexcept;
  [[nodiscard]] virtual Character* asCharacter() noexcept;
};