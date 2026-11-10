#pragma once

#include "core/MapObject/MapObject.h"
#include "engine/model/IGame/Coords.h"
#include "engine/model/IGraphics/Visitor.h"

enum class OverworldObstacleType : char { DRIED_TREE, GREEN_TREE };

class OverworldObstacle : public MapObject {
  OverworldObstacleType type_;

 public:
  OverworldObstacle( OverworldObstacleType type, CoordPair coords );
  void accept( Visitor& v ) const override;
  [[nodiscard]] OverworldObstacleType getType() const;
};