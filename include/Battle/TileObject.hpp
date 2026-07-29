#pragma once
// Autor: Tomasz Naszkowski
/* Zawarość klasy TileObject:
  - klasa TileObject jest interfajsem dla obiektów, które mogą być umieszczane na kafelkach w grze.
*/

class TileObject {
 private:
  bool traversable_;

 public:
  TileObject( bool traversable ) noexcept : traversable_( traversable ) {};
  [[nodiscard]] bool isTraversable() const noexcept {
    return traversable_;
  }
};