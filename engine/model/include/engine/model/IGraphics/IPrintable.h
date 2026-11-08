#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Printable jest interfejsem do wizualizacji obiektów

#include "engine/model/IGraphics/Visitor.h"

class IPrintable {  // NOLINT(cppcoreguidelines-special-member-functions)
 public:
  virtual void accept( GfxVisitor& ) const noexcept = 0;
  virtual ~IPrintable() = default;
};