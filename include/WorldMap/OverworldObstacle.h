#pragma once

#include <cstdint>

#include "Graphics/Visitor.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"

enum class OverworldObstacleType : uint8_t { DRIED_TREE, GREEN_TREE, COUNT };

class OverworldObstacle : public MapObject {
  OverworldObstacleType type_;

 public:
  OverworldObstacle( OverworldObstacleType type, CoordPair coords );
  void accept( Visitor& v ) const override;
  [[nodiscard]] OverworldObstacleType getType() const;
};