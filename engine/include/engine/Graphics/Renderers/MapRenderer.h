#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "core/WorldMap/WorldMap.h"
#include "engine/Graphics/Renderers/IRenderer.hpp"
#include "engine/IGame/Coords.h"


class MapRenderer : public IRenderer<WorldMap> {
 private:
  CoordPair center_coords_;

  void renderGridWithFun( void ( MapRenderer::*fun )( int, int ) const ) const noexcept;

  void renderBackgroundTile( int x, int y ) const noexcept;
  void renderObject( int x, int y ) const noexcept;

  // void renderObjects();

 public:
  //     IRenderer(const SpriteVisitor& sprite_visitor, const T& object) :
  // sprite_visitor_(sprite_visitor), object_(object) {};
  MapRenderer( sf::RenderTexture& target_render_texture, const WorldMap& object, CoordPair center_coords );
  ~MapRenderer() override = default;
  void render() override;
};