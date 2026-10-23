#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Printable jest interfejsem do wizualizacji obiektów

#include "engine/model/IGraphics/Visitor.h"

class IPrintable { // NOLINT(cppcoreguidelines-special-member-functions)
 public:
  virtual void accept( Visitor& ) const = 0;
  virtual ~IPrintable() = default;
};