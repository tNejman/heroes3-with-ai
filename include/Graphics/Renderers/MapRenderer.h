#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

#include "Graphics/Renderers/IRenderer.hpp"
#include "Graphics/SpriteVisitor.h"
#include "Miscellaneous/Coords.h"
#include "WorldMap/WorldMap.h"

class MapRenderer : public IRenderer<WorldMap> {
 private:
  CoordPair center_coords_;

  void renderGrid() const;
  void renderObjects() const;

 public:
  //     IRenderer(const SpriteVisitor& sprite_visitor, const T& object) :
  // sprite_visitor_(sprite_visitor), object_(object) {};
  MapRenderer( sf::RenderWindow& window, const WorldMap& object, CoordPair center_coords );
  ~MapRenderer() override = default;
  void render() override;
};