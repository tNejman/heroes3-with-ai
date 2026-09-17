#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Resource pozwala na zarządzanie zasobami

#include <cstdint>

#include "engine/Graphics/IPrintable.h"
#include "engine/Graphics/Visitor.h"

enum class ResourceType : char { TIMBER, MERCURY, STONE, SULFUR, CRYSTAL, GEMSTONE, MONEY, COUNT };

class Resource : public IPrintable {
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