#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Obstacle:
  - Klasa Obstacle odpowiada za przeszkody na polu bitwy.
  - Przeszkody są reprezentowane jako obiekty, które mogą być umieszczane na polu bitwy.
*/

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <string_view>
#include <utility>

#include "Battle/TileObject.hpp"
#include "Graphics/Printable.h"

class Visitor;

class Obstacle : public Printable, public TileObject {
 public:
  Obstacle( std::string name ) : Printable(), TileObject( false ), name_( std::move( name ) ) {};
  [[nodiscard]] sf::Texture& accept( Visitor& vis ) const override {
    return vis.visit( *this );
  }
  [[nodiscard]] const std::string& getName() const {
    return name_;
  }

 private:
  std::string name_;
};