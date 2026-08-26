#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Printable jest interfejsem do wizualizacji obiektów

#include "Graphics/Visitor.h"

class Printable {
 public:
  virtual void accept( Visitor& ) const = 0;
  virtual ~Printable() = default;
};