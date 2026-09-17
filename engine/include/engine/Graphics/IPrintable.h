#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Printable jest interfejsem do wizualizacji obiektów

#include "engine/Graphics/Visitor.h"

class IPrintable {
 public:
  virtual void accept( Visitor& ) const = 0;
  virtual ~IPrintable() = default;
};