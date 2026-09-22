#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <functional>

#include "core/Game/Game.h"
#include "engine/Graphics/Renderers/IRenderer.hpp"

class GameRenderer : public IRenderer<Game> {
 private:
  std::reference_wrapper<sf::RenderWindow> window_;

 public:
  GameRenderer( sf::RenderWindow& window, sf::RenderTexture& target_render_texture, const Game& game ) noexcept;
  void render() override;
};