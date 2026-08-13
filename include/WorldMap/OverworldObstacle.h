#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>

#include "Graphics/Visitor.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"

class OverworldObstacle : public MapObject {
  const std::string name_;

 public:
  OverworldObstacle( std::string name, CoordPair coords );
  sf::Texture& accept( Visitor& v ) const override;
  [[nodiscard]] const std::string& getName() const;
};