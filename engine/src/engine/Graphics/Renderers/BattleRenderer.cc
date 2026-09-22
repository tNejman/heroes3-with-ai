#include "engine/Graphics/Renderers/BattleRenderer.h"

#include <engine/Graphics/GraphicsLib.h>
#include <engine/Graphics/SpriteFactory.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cstddef>
#include <engine/Graphics/Renderers/IRenderer.hpp>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "aux/Err.hpp"
#include "core/Battle/Battle.h"
#include "core/Battle/Moves/AttackMove.h"
#include "core/Battle/Moves/MoveMove.h"
#include "core/Battle/Moves/WaitMove.h"
#include "core/Battle/Tile.h"  // IWYU pragma: keep
#include "core/Misc/ProjectLib.h"
#include "core/Unit/UnitStack.h"
#include "engine/IGame/Coords.h"

[[nodiscard]] std::pair<int, int> BattleRenderer::getHexagonOffset( CoordPair coords ) noexcept {
  int offset_x = graphics::BATTLE_MAP_SPRITE_INITIAL_OFFSET_X_ODD + ( coords.x_ * graphics::BATTLE_MAP_SPRITE_X_DELTA );
  int offset_y = graphics::BATTLE_MAP_SPRITE_INITIAL_OFFSET_Y_ODD
                 + ( ( 5 - ( coords.y_ / 2 ) ) * graphics::BATTLE_MAP_SPRITE_Y_DELTA );

  if ( coords.y_ % 2 == 0 ) {
    offset_x += graphics::BATTLE_MAP_SPRITE_ADJUST_EVEN_X;
    offset_y += graphics::BATTLE_MAP_SPRITE_ADJUST_EVEN_Y;
  }
  return { offset_x, offset_y };
}

void BattleRenderer::renderBackground() noexcept {
  Terrain background = object_.get().getBattlefield()->getBackground();
  sf::Sprite background_sprite =
      SpriteFactory::getSpriteFromBindingV( Tagged<Terrain, SpriteDomain::BATTLE>( background ) );
  target_render_texture_.get().draw( background_sprite );
}
void BattleRenderer::renderCharacters() noexcept {
  const auto attacker = object_.get().getAttacker();
  const auto defender = object_.get().getDefender();

  sf::Sprite attacker_sprite =
      SpriteFactory::getSpriteFromBindingV( attacker->getCharacterType(), CharacterMoveDirection::DOWN_RIGHT );
  attacker_sprite.setPosition( { 0, 0 } );
  target_render_texture_.get().draw( attacker_sprite );

  sf::Sprite defender_sprite =
      SpriteFactory::getSpriteFromBindingV( attacker->getCharacterType(), CharacterMoveDirection::DOWN_LEFT );
  defender_sprite.setPosition( { static_cast<float>( static_cast<int>( target_render_texture_.get().getSize().x )
                                                     - defender_sprite.getTextureRect().size.x ),
                                 0 } );
  target_render_texture_.get().draw( defender_sprite );

  // TODO finish
}
void BattleRenderer::renderGrid() noexcept {
  const static sf::Texture combined_hexagons_texture = [] {
    sf::RenderTexture combined_hexagons{ sf::Vector2u{ graphics::WINDOW_WIDTH, graphics::WINDOW_HEIGHT } };
    sf::Sprite hex_sprite = SpriteFactory::getSpriteFromBindingV( HexagonType::EMPTY );
    combined_hexagons.clear( sf::Color::Transparent );

    for ( int x = 0; x < MAP_WIDTH_BF; ++x ) {
      for ( int y = 0; y < MAP_HEIGHT_BF; ++y ) {
        auto [offset_x, offset_y] = getHexagonOffset( { x, y } );
        hex_sprite.setPosition( sf::Vector2f{ static_cast<float>( offset_x ), static_cast<float>( offset_y ) } );
        combined_hexagons.draw( hex_sprite );
      }
    }
    combined_hexagons.display();
    return combined_hexagons.getTexture();
  }();

  target_render_texture_.get().draw( sf::Sprite{ combined_hexagons_texture } );
}

void BattleRenderer::renderMoves() noexcept {
  for ( const auto& move : object_.get().getPossibleMoves() ) {
    // TODO change moves to new ones with std::variant rather than use dynamic cast here
    std::pair<int, int> offset;
    std::optional<sf::Sprite> hex_sprite;
    if ( const auto* m_move = dynamic_cast<MoveMove*>( move.get() ) ) {
      offset = getHexagonOffset( m_move->destinationCoords() );
      hex_sprite = SpriteFactory::getSpriteFromBindingV( HexagonType::MOVE );
    } else if ( const auto* a_move = dynamic_cast<AttackMove*>( move.get() ) ) {
      offset = getHexagonOffset( a_move->destinationCoords() );
      hex_sprite = SpriteFactory::getSpriteFromBindingV( HexagonType::ATTACK );
    } else if ( nullptr != dynamic_cast<WaitMove*>( move.get() ) ) {
      offset = getHexagonOffset( object_.get().getUnitInAction()->getCoordsInBattle() );
      hex_sprite = SpriteFactory::getSpriteFromBindingV( HexagonType::IN_ACTION );
    }
    err::passCondOrAbort( hex_sprite.has_value(), "unknown move" );

    sf::Sprite& actual_sprite = hex_sprite.value();
    actual_sprite.setPosition(
        sf::Vector2f{ static_cast<float>( offset.first ), static_cast<float>( offset.second ) } );
    target_render_texture_.get().draw( actual_sprite );
  }
}
void BattleRenderer::renderObjects() noexcept {
  static constexpr int FEET_FROM_TOP_OFFSET = 40;

  for ( size_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( size_t y = 0; y < MAP_HEIGHT_BF; ++y ) {
      if ( object_.get().getBattlefield()->getGrid()[x][y]->getObject() == nullptr
           || object_.get().getBattlefield()->getGrid()[x][y]->getObject()->asUnit() == nullptr ) {
        continue;
      }
      const UnitStack* unit = object_.get().getBattlefield()->getGrid()[x][y]->getObject()->asUnit();

      sf::Sprite unit_sprite = SpriteFactory::getSpriteFromBindingV( unit->getData().type_ );
      auto [tile_offset_x, tile_offset_y] = getHexagonOffset( unit->getCoordsInBattle() );
      auto unit_draw_x = static_cast<float>( tile_offset_x )
                         + ( static_cast<float>( graphics::HEXAGON_SPRITE_WIDTH ) / 2 )
                         - ( static_cast<float>( unit_sprite.getTextureRect().size.x ) / 2 );
      auto unit_draw_y = static_cast<float>( tile_offset_y + FEET_FROM_TOP_OFFSET
                                             - SpriteFactory::getFootHeightForUnit( unit->getData().type_ ) );
      unit_sprite.setPosition( sf::Vector2f{ unit_draw_x, unit_draw_y } );

      if ( std::ranges::find_if(
               object_.get().getDefender()->army().getParty(),
               [&]( const std::optional<UnitStack>& u ) { return u.has_value() && unit == std::addressof( *u ); } )
           != object_.get().getDefender()->army().getParty().end() ) {
        SpriteFactory::flipSpriteHorizontally( unit_sprite );
      }

      target_render_texture_.get().draw( unit_sprite );

      /* === draw health === */
      static const sf::Texture health_box_tex = [] {
        sf::Texture tex;
        err::passCondOrAbort( tex.loadFromFile( "assets/sprites/battle/aux/unit_health_template.png" ) );
        return tex;
      }();
      sf::Sprite health_box_sprite{ health_box_tex };
      health_box_sprite.setPosition( sf::Vector2f{ unit_draw_x, unit_draw_y } );
      target_render_texture_.get().draw( health_box_sprite );

      sf::Font font;
      err::passCondOrAbort( font.openFromFile( "assets/fonts/DejaVuSans.ttf" ) );
      sf::Text health_num( font, std::to_string( unit->getSize() ), 20 );
      health_num.setFillColor( sf::Color::White );
      health_num.setPosition( sf::Vector2f{ unit_draw_x, unit_draw_y } );
      target_render_texture_.get().draw( health_num );
    }
  }
}

BattleRenderer::BattleRenderer( sf::RenderTexture& target_render_texture, const Battle& battle ) noexcept
    : IRenderer<Battle>( target_render_texture, battle ) {
}

void BattleRenderer::render() {
  renderBackground();
  renderCharacters();
  renderGrid();
  renderMoves();
  renderObjects();
}