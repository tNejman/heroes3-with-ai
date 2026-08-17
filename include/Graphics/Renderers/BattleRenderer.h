#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <utility>

#include "Battle/Battle.h"
#include "Graphics/Renderers/IRenderer.hpp"
#include "Miscellaneous/Coords.h"

class BattleRenderer : public IRenderer<Battle> {
 private:
  [[nodiscard]] static std::pair<int, int> getHexagonOffset( CoordPair coords ) noexcept;

  void renderBackground() noexcept;
  void renderCharacters() noexcept;
  void renderGrid() noexcept;
  void renderMoves() noexcept;
  void renderObjects() noexcept;

 public:
  BattleRenderer( sf::RenderWindow& window, const Battle& battle ) noexcept;
  void render() override;
};