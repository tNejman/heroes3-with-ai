#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

#include "Graphics/Renderers/IRenderer.hpp"
#include "Graphics/SpriteVisitor.h"
#include "Miscellaneous/Coords.h"
#include "WorldMap/WorldMap.h"

class MapRenderer : public IRenderer<WorldMap> {
 private:
  void renderGrid( sf::RenderWindow& window, CoordPair center_coords ) const;
  void renderObjects( sf::RenderWindow& window, CoordPair center_coords ) const;

 public:
  //     IRenderer(const SpriteVisitor& sprite_visitor, const T& object) :
  // sprite_visitor_(sprite_visitor), object_(object) {};
  MapRenderer( const std::shared_ptr<SpriteVisitor>& sprite_visitor, const WorldMap& object )
      : IRenderer( sprite_visitor, object ) {};
  ~MapRenderer() override = default;
  void render( sf::RenderWindow& window, CoordPair center_coords ) override;
};