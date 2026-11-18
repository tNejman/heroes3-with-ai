#pragma once

#include "engine/model/IGame/Coords.h"
#include "engine/model/IGraphics/IPrintable.h"
#include "engine/model/IGraphics/Visitor.h"

#include "aux/Visitor.hpp"

#include "core/MapObject/MapObject.h"

enum class OverworldObstacleType : char { DRIED_TREE, GREEN_TREE };

class OverworldObstacle : public MapObject, public visitor::Visitable<OverworldObstacle, IPrintable, GfxVisitor> {
  OverworldObstacleType type_;

 public:
  [[nodiscard]] OverworldObstacle( OverworldObstacleType type, CoordPair coords ) noexcept;
  [[nodiscard]] OverworldObstacleType getType() const noexcept;
};