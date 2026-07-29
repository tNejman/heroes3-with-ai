#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Resource pozwala na zarządzanie zasobami

// #include <SFML/Graphics.hpp>

#include <SFML/Graphics/Texture.hpp>

#include "Graphics/Printable.h"
#include "Graphics/Visitor.h"

enum class ResourceType { TIMBER, MERCURY, STONE, SULFUR, CRYSTAL, GEMSTONE, MONEY };

class Resource : public Printable {
 private:
  ResourceType type_;
  int amount_;

 public:
  Resource() = delete;
  Resource( ResourceType type, int amount );
  sf::Texture& accept( Visitor& v ) const override;
  [[nodiscard]] ResourceType getType() const noexcept;
  [[nodiscard]] int getAmount() const noexcept;
};