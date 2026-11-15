#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "engine/model/IGame/Coords.h"

#include "engine/platform/Graphics/Renderers/IRenderer.hpp"

#include "core/WorldMap/WorldMap.h"

class MapRenderer : public IRenderer<WorldMap> {  // NOLINT(cppcoreguidelines-special-member-functions)
 private:
  CoordPair center_coords_;

  void renderGridWithFun( void ( MapRenderer::*fun )( int, int ) const ) const noexcept;

  void renderBackgroundTile( int x, int y ) const noexcept;
  void renderObject( int x, int y ) const noexcept;

 public:
  [[nodiscard]] MapRenderer( sf::RenderTexture& target_render_texture, const WorldMap& object,
                             CoordPair center_coords ) noexcept;
  ~MapRenderer() noexcept override = default;
  void render() noexcept override;
};