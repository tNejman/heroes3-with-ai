#pragma once

#include <functional>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>

#include "engine/platform/Graphics/Renderers/IRenderer.hpp"

#include "core/Game/Game.h"

class GameRenderer : public IRenderer<Game> {
 private:
  std::reference_wrapper<sf::RenderWindow> window_;

 public:
  [[nodiscard]] GameRenderer( sf::RenderWindow& window, sf::RenderTexture& target_render_texture,
                              const Game& game ) noexcept;
  void render() noexcept override;
};