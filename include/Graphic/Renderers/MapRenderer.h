#pragma once

#include "Exceptions/NotOpenWindowException.hpp"
#include "Graphic/Renderers/IRenderer.hpp"
#include "WorldMap/WorldMap.h"

class MapRenderer : public IRenderer<WorldMap> {
 public:
  //     IRenderer(const SpriteVisitor& sprite_visitor, const T& object) :
  // sprite_visitor_(sprite_visitor), object_(object) {};
  MapRenderer( std::shared_ptr<SpriteVisitor> sprite_visitor, std::shared_ptr<WorldMap> object ) : IRenderer( sprite_visitor, object ) {};
  ~MapRenderer() override = default;
  void render( sf::RenderWindow& window, const CoordPair center_coords ) override;
  void renderGrid( sf::RenderWindow& window, const CoordPair center_coords );
  void renderObjects( sf::RenderWindow& window, const CoordPair center_coords );
};