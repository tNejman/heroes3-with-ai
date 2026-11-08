#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Obstacle:
  - Klasa Obstacle odpowiada za przeszkody na polu bitwy.
  - Przeszkody są reprezentowane jako obiekty, które mogą być umieszczane na polu bitwy.
*/

#include <string>
#include <utility>

#include "aux/Visitor.hpp"
#include "core/Battle/TileObject.hpp"
#include "engine/model/IGraphics/IPrintable.h"
#include "engine/model/IGraphics/Visitor.h"

class Visitor;

class Obstacle : public visitor::Visitable<Obstacle, IPrintable, GfxVisitor>, public TileObject {
 public:
  Obstacle( std::string name ) : TileObject( false ), name_( std::move( name ) ) {};

  [[nodiscard]] const std::string& getName() const {
    return name_;
  }

 private:
  std::string name_;
};