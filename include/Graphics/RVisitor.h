#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

#include "Game/GameStateBattle.h"
#include "Game/GameStateOverworld.h"
#include "Graphics/Renderers/MapRenderer.h"
#include "Graphics/SpriteVisitor.h"
#include "IRVisitor.h"
#include "Miscellaneous/Coords.h"

class RVisitor : public IRVisitor {
 private:
  sf::RenderWindow& window_;
  CoordPair center_coords_;

 public:
  RVisitor( sf::RenderWindow& window, CoordPair center_coords ) : window_( window ), center_coords_( center_coords ) {
  }

  void visit( const GameStateOverworld& s ) noexcept override {
    MapRenderer{ std::make_shared<SpriteVisitor>(), s.viewMap() }.render( window_, center_coords_ );
  }

  void visit( const GameStateBattle& s ) noexcept override {
    auto sprite_visitor = std::make_shared<SpriteVisitor>();
    sf::Sprite sprite{ s.viewBattle().accept( *sprite_visitor ) };
    window_.draw( sprite );
  }
};