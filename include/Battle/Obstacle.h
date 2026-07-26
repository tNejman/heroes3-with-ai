#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Obstacle:
  - Klasa Obstacle odpowiada za przeszkody na polu bitwy.
  - Przeszkody są reprezentowane jako obiekty, które mogą być umieszczane na polu bitwy.
*/
#include "Battle/TileObject.h"
#include "Miscellaneous/Printable.h"

class Obstacle : public Printable, public TileObject {
 public:
  Obstacle( std::string name ) : Printable(), TileObject( false ), name_( name ) {};
  virtual sf::Texture& accept( Visitor& v ) const override { return v.visit( *this ); }
  std::string getName() const { return name_; }

 private:
  std::string name_;
};