#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Printable jest interfejsem do wizualizacji obiektów

// #include <SFML/Graphics.hpp>

#include "Graphic/Visitor.h"

class Printable {
 public:
  virtual sf::Texture& accept( Visitor& v ) const = 0;
  virtual ~Printable() = default;
};