#pragma once
// Autor: Tomasz Naszkowski
/* Zawarość klasy TileObject:
  - klasa TileObject jest interfajsem dla obiektów, które mogą być umieszczane na kafelkach w grze.
*/
#include <array>
#include <memory>
#include <string>
#include <vector>

class TileObject {
 private:
  bool passable_;
  std::string name_;

 public:
  TileObject( std::string name ) : passable_( false ), name_( name ) {};
  TileObject() : passable_( false ), name_( "" ) {};
  TileObject( bool passable ) : passable_( passable ) {};
  const std::string& getName() const;
};