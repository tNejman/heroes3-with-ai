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
  [[nodiscard]] constexpr TileObject( bool traversable ) noexcept : traversable_( traversable ) {};
  constexpr virtual ~TileObject() = default;
  [[nodiscard]] constexpr bool isTraversable() const noexcept {
    return traversable_;
  }
  [[nodiscard]] constexpr virtual const UnitStack* asUnit() const noexcept {
    return nullptr;
  }
  [[nodiscard]] constexpr virtual UnitStack* asUnit() noexcept {
    return nullptr;
  }
};