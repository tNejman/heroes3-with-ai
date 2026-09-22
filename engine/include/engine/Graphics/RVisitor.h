#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
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
  std::reference_wrapper<sf::RenderTexture> target_render_texture_;
  std::reference_wrapper<const game::Context> context_;

 public:
  RVisitor( sf::RenderTexture& target_render_texture, const game::Context& context )
      : target_render_texture_( target_render_texture ), context_( context ) {
  }

  void visit( const game::StateOverworld& s ) noexcept override {
    CoordPair center_coords = context_.get().getCurrentCharacter().getCoords();
    MapRenderer{ target_render_texture_, s.viewMap(), center_coords }.render();
  }

  void visit( const game::StateBattle& s ) noexcept override {
    BattleRenderer{ target_render_texture_, s.viewBattle() }.render();
  }
};