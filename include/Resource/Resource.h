#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Resource pozwala na zarządzanie zasobami

// #include <SFML/Graphics.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <cstdint>
#include <string>

#include "Graphics/Visitor.h"
#include "Miscellaneous/Printable.h"

enum class availableResource { TIMBER, MERCURY, STONE, SULFER, CRYSTAL, GEMSTONE, MONEY };

class Resource : public Printable {
 private:
  availableResource resource_;
  uint32_t resourceAmount_;

 public:
  Resource( availableResource resource, uint32_t resource_amount )
      : resource_( resource ), resourceAmount_( resource_amount ) {};
  virtual sf::Texture& accept( Visitor& v ) const override {
    return v.visit( *this );
  }
  const std::string& getName() const noexcept;
  uint32_t getAmount() const noexcept;
};