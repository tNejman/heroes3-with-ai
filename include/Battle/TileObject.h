#pragma once
// Autor: Tomasz Naszkowski
/* Zawarość klasy TileObject:
  - klasa TileObject jest interfajsem dla obiektów, które mogą być umieszczane na kafelkach w grze.
*/
#include <string>
#include <utility>

class TileObject {
 private:
  bool passable_;
  std::string name_;

 public:
  TileObject( std::string name ) : passable_( false ), name_( std::move( name ) ) {};
  TileObject() : passable_( false ) {};
  TileObject( bool passable ) : passable_( passable ) {};
  [[nodiscard]] bool isPassable() const noexcept;
  [[nodiscard]] const std::string& getName() const;
};