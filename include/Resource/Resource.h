#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Resource pozwala na zarządzanie zasobami

// #include <SFML/Graphics.hpp>

#include "Miscellaneous/Printable.h"
#include "Miscellaneous/ProjectLib.h"

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
  std::string getName() const;
};