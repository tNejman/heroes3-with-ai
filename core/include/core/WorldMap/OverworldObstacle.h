#pragma once

#include "engine/Graphics/Visitor.h"
#include "core/MapObject/MapObject.h"
#include "engine/IGame/Coords.h"

enum class OverworldObstacleType : char { DRIED_TREE, GREEN_TREE, COUNT };

class OverworldObstacle : public MapObject {
  OverworldObstacleType type_;

 public:
  OverworldObstacle( OverworldObstacleType type, CoordPair coords );
  void accept( Visitor& v ) const override;
  [[nodiscard]] OverworldObstacleType getType() const;
};