#pragma once
// Autor: Tomasz Nejman

// #include <SFML/Graphics.hpp>

#include <string>

#include "Graphics/Printable.h"
#include "WorldMap/MapObject.h"

class Building : public MapObject {
 public:
  // virtual sf::Texture& accept(Visitor& v) const override {return v.visit(*this); }
  Building( const std::string& name ) : name_( name ) {
  }
  std::string getName() const;

 private:
  const std::string name_;
};