#pragma once

#include "WorldMap/MapObject.h"

class OverworldObstacle : public MapObject {
  const std::string name_;

 public:
  OverworldObstacle( const std::string& name, CoordPair coords );
  sf::Texture& accept( Visitor& v ) const override;
  const std::string& getName() const;
};