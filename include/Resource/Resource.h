#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Resource pozwala na zarządzanie zasobami

#include <cstdint>

#include "Graphics/Printable.h"
#include "Graphics/Visitor.h"

enum class ResourceType : char { TIMBER, MERCURY, STONE, SULFUR, CRYSTAL, GEMSTONE, MONEY, COUNT };

class Resource : public Printable {
 private:
  ResourceType type_;
  int amount_;

 public:
  Resource() = delete;
  Resource( ResourceType type, int amount );
  void accept( Visitor& v ) const override;
  [[nodiscard]] ResourceType getType() const noexcept;
  [[nodiscard]] int getAmount() const noexcept;
};