#pragma once
// Autor: Tomasz Nejman

#include <SFML/Graphics/Texture.hpp>
#include <string>

#include "Graphics/Visitor.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"

class Building : public MapObject {
 private:
  std::string name_;

 public:
  Building( CoordPair coords, std::string name );
  sf::Texture& accept( Visitor& v ) const override;

  [[nodiscard]] std::string getName() const;
};