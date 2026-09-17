#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

#include "core/Game/Game.h"
#include "engine/Graphics/Renderers/IRenderer.hpp"

class GameRenderer : public IRenderer<Game> {
 public:
  GameRenderer( sf::RenderWindow& window, const Game& game );
  void render() override;
};