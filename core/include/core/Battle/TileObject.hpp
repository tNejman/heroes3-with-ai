#pragma once
// Autor: Tomasz Naszkowski
/* Zawarość klasy TileObject:
  - klasa TileObject jest interfajsem dla obiektów, które mogą być umieszczane na kafelkach w grze.
*/

class UnitStack;

class TileObject {  // NOLINT(cppcoreguidelines-special-member-functions)
 private:
  bool traversable_;

 public:
  TileObject( bool traversable ) noexcept : traversable_( traversable ) {};
  virtual ~TileObject() = default;
  [[nodiscard]] bool isTraversable() const noexcept {
    return traversable_;
  }
  [[nodiscard]] virtual UnitStack* asUnit() noexcept {
    return nullptr;
  }
};