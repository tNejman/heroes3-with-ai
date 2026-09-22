#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <utility>

#include "core/Battle/Battle.h"
#include "engine/Graphics/Renderers/IRenderer.hpp"
#include "engine/IGame/Coords.h"

class BattleRenderer : public IRenderer<Battle> {
 private:
  [[nodiscard]] static std::pair<int, int> getHexagonOffset( CoordPair coords ) noexcept;

  void renderBackground() noexcept;
  void renderCharacters() noexcept;
  void renderGrid() noexcept;
  void renderMoves() noexcept;
  void renderObjects() noexcept;

 public:
  BattleRenderer( sf::RenderTexture& target_render_texture, const Battle& battle ) noexcept;
  void render() override;
};