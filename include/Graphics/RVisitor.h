#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <functional>

#include "Game/GameContext.h"
#include "Game/GameStateBattle.h"
#include "Game/GameStateOverworld.h"
#include "Graphics/Renderers/BattleRenderer.h"
#include "Graphics/Renderers/MapRenderer.h"
#include "IRVisitor.h"
#include "Miscellaneous/Coords.h"

class RVisitor : public IRVisitor {
 private:
  std::reference_wrapper<sf::RenderWindow> window_;
  std::reference_wrapper<const GameContext> context_;

 public:
  RVisitor( sf::RenderWindow& window, const GameContext& context ) : window_( window ), context_( context ) {
  }

  void visit( const GameStateOverworld& s ) noexcept override {
    CoordPair center_coords = context_.get().getCurrentCharacter().getCoords();
    MapRenderer{ window_, s.viewMap(), center_coords }.render();
  }

  void visit( const GameStateBattle& s ) noexcept override {
    BattleRenderer{ window_, s.viewBattle() }.render();
  }
};