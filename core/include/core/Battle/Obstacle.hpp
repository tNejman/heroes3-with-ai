#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Obstacle:
  - Klasa Obstacle odpowiada za przeszkody na polu bitwy.
  - Przeszkody są reprezentowane jako obiekty, które mogą być umieszczane na polu bitwy.
*/

#include <string>
#include <utility>

#include "engine/model/IGraphics/IPrintable.h"
#include "engine/model/IGraphics/Visitor.h"

#include "aux/Visitor.hpp"

#include "core/Battle/TileObject.hpp"

class Visitor;

class Obstacle : public visitor::Visitable<Obstacle, IPrintable, GfxVisitor>, public TileObject {
 public:
  [[nodiscard]] Obstacle( std::string name ) noexcept : TileObject( false ), name_( std::move( name ) ) {};

  [[nodiscard]] const std::string& getName() const noexcept {
    return name_;
  }

 private:
  std::string name_;
};