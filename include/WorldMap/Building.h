#pragma once
// Autor: Tomasz Nejman

// #include <SFML/Graphics.hpp>

#include <string>
#include <utility>

#include "MapObject/MapObject.h"

class Building : public MapObject {
 private:
  std::string name_;

 public:
  // virtual sf::Texture& accept(Visitor& v) const override {return v.visit(*this); }
  Building( std::string name ) : MapObject( { .x_ = 0, .y_ = 0 } ), name_( std::move( name ) ) {
  }
  [[nodiscard]] std::string getName() const;
};