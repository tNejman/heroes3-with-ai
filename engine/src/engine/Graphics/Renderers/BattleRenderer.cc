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
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cstddef>
#include <engine/Graphics/Renderers/IRenderer.hpp>
#include <memory>
#include <optional>
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
  window_.get().draw( background_sprite );
}
void BattleRenderer::renderCharacters() noexcept {
  const auto attacker = object_.get().getAttacker();
  const auto defender = object_.get().getDefender();

  sf::Sprite attacker_sprite =
      SpriteFactory::getSpriteFromBindingV( attacker->getCharacterType(), CharacterMoveDirection::DOWN_RIGHT );
  attacker_sprite.setPosition( { 0, 0 } );
  window_.get().draw( attacker_sprite );

  sf::Sprite defender_sprite =
      SpriteFactory::getSpriteFromBindingV( attacker->getCharacterType(), CharacterMoveDirection::DOWN_LEFT );
  defender_sprite.setPosition(
      { static_cast<float>( static_cast<int>( window_.get().getSize().x ) - defender_sprite.getTextureRect().size.x ),
        0 } );
  window_.get().draw( defender_sprite );

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

  window_.get().draw( sf::Sprite{ combined_hexagons_texture } );
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
    window_.get().draw( actual_sprite );
  }
}
void BattleRenderer::renderObjects() noexcept {
  static constexpr int FEET_FROM_TOP_OFFSET = 40;

  for ( size_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( size_t y = 0; y < MAP_HEIGHT_BF; ++y ) {
      if ( const UnitStack* unit = object_.get().getBattlefield()->getGrid()[x][y]->getObject()->asUnit() ) {
        sf::Sprite unit_sprite = SpriteFactory::getSpriteFromBindingV( unit->getData().type_ );
        auto [tile_offset_x, tile_offset_y] = getHexagonOffset( unit->getCoordsInBattle() );
        int unit_draw_x = tile_offset_x + ( graphics::HEXAGON_SPRITE_WIDTH / 2 )
                          - ( static_cast<int>( unit_sprite.getTextureRect().size.x ) / 2 );
        int unit_draw_y =
            tile_offset_y + FEET_FROM_TOP_OFFSET - SpriteFactory::getFootHeightForUnit( unit->getData().type_ );
        unit_sprite.setPosition( sf::Vector2f{ static_cast<float>( unit_draw_x ), static_cast<float>( unit_draw_y ) } );

        if ( std::ranges::find_if(
                 object_.get().getDefender()->army().getParty(),
                 [&]( const std::optional<UnitStack>& u ) { return u.has_value() && unit == std::addressof( *u ); } )
             != object_.get().getDefender()->army().getParty().end() ) {
          SpriteFactory::flipSpriteHorizontally( unit_sprite );
        }

        window_.get().draw( unit_sprite );

        /* === draw health === */
        sf::Font health_num;
        if ()
      }
    }
  }
}

BattleRenderer::BattleRenderer( sf::RenderWindow& window, const Battle& battle ) noexcept
    : IRenderer<Battle>( window, battle ) {
}

void BattleRenderer::render() {
  renderBackground();
  renderCharacters();
  renderGrid();
  renderMoves();
  renderObjects();
}