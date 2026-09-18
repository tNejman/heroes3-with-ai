#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <functional>

#include "core/Game/Context.h"
#include "core/Game/StateBattle.h"
#include "core/Game/StateOverworld.h"
#include "engine/Graphics/IRVisitor.h"
#include "engine/Graphics/Renderers/BattleRenderer.h"
#include "engine/Graphics/Renderers/MapRenderer.h"
#include "engine/IGame/Coords.h"

class RVisitor : public IRVisitor {
 private:
  std::reference_wrapper<sf::RenderWindow> window_;
  std::reference_wrapper<const game::Context> context_;

 public:
  RVisitor( sf::RenderWindow& window, const game::Context& context ) : window_( window ), context_( context ) {
  }

  void visit( const game::StateOverworld& s ) noexcept override {
    CoordPair center_coords = context_.get().getCurrentCharacter().getCoords();
    MapRenderer{ window_, s.viewMap(), center_coords }.render();
  }

  void visit( const game::StateBattle& s ) noexcept override {
    BattleRenderer{ window_, s.viewBattle() }.render();
  }
};