#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Game/Game.h"
#include "Graphics/Renderers/IRenderer.hpp"
#include "Miscellaneous/Coords.h"

class GameRenderer : public IRenderer<Game> {
 public:
  GameRenderer( const Game& game );
  void render( sf::RenderWindow& window, CoordPair center_coords ) override;
};