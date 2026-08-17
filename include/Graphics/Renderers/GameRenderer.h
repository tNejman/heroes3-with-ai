#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

#include "Game/Game.h"
#include "Graphics/Renderers/IRenderer.hpp"

class GameRenderer : public IRenderer<Game> {
 public:
  GameRenderer( sf::RenderWindow& window, const Game& game );
  void render() override;
};