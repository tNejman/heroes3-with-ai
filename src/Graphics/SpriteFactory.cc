#include "Graphics/SpriteFactory.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <string_view>

#include "Exceptions/Err.hpp"
#include "Miscellaneous/DiscardReturn.hpp"
#include "Miscellaneous/ProjectLib.h"

[[nodiscard]] sf::Sprite SpriteFactory::cropTexture( const sf::Texture& texture, sf::Vector2<int> ltc_pos,
                                                     sf::Vector2<int> size ) noexcept {
  return sf::Sprite{ texture, sf::IntRect{ ltc_pos, size } };
}

[[nodiscard]] sf::Texture SpriteFactory::loadTextureOrAbort( std::string_view path ) noexcept {
  sf::Texture t;
  err::passCondOrAbort( t.loadFromFile( path ), "couldn't load: ", path );
  return t;
}

void SpriteFactory::flipSpriteHorizontally( sf::Sprite& sprite ) noexcept {
  const float left_before = sprite.getGlobalBounds().position.x;
  sprite.scale( { -1.f, 1.f } );
  const float left_after = sprite.getGlobalBounds().position.x;
  sprite.move( { left_before - left_after, 0.f } );
}

void SpriteFactory::eraseCharactersTextureCornerMarkers( sf::Texture& texture, unsigned int width,
                                                         unsigned int height ) noexcept {
  sf::Image image = texture.copyToImage();
  const sf::Vector2u size = image.getSize();
  for ( unsigned int y = height - 1; y < size.y; y += height ) {
    for ( unsigned int x = width - 1; x < size.x; x += width ) {
      image.setPixel( { x, y }, sf::Color::Transparent );
    }
  }
  DISCARD_RETURN() texture.loadFromImage( image );
}

/* === @PUBLIC === */

// [[nodiscard]] sf::Sprite SpriteFactory ::getSpriteFromBinding( Terrain t ) noexcept {
// }

[[nodiscard]] sf::Sprite SpriteFactory ::getSpriteFromBinding( CharacterType ct, CharacterMoveDirection cmd ) noexcept {
  static constexpr int HERO_SPRITE_WIDTH = 96;
  static constexpr int HERO_SPRITE_HEIGHT = 64;

  static constexpr std::string_view HEROES_SPRITES_FILE_PATH = "sprites/heroes_adventure.png";
  static const sf::Texture heroes_sprite_texture = [] {
    auto tex = loadTextureOrAbort( HEROES_SPRITES_FILE_PATH );
    eraseCharactersTextureCornerMarkers( tex, HERO_SPRITE_WIDTH, HERO_SPRITE_HEIGHT );
    return tex;
  }();

  enum horizontal_offset : int8_t {
    FACING_DOWN = 0,
    FACING_DOWN_RIGHT = 1,
    FACING_RIGHT = 2,
    FACING_UP_RIGHT = 3,
    FACING_UP = 4
  };

  const int horizontal_multiplier = [&] {
    switch ( cmd ) {
      // sprites are only facing right so assign mirrored versions and flip later
      // also leave duplicate branches; enum best switched in declared order
      case CharacterMoveDirection::UP_LEFT: return horizontal_offset::FACING_UP_RIGHT;
      case CharacterMoveDirection::UP: return horizontal_offset::FACING_UP;
      case CharacterMoveDirection::UP_RIGHT: return horizontal_offset::FACING_UP_RIGHT;
      case CharacterMoveDirection::RIGHT: return horizontal_offset::FACING_RIGHT;
      case CharacterMoveDirection::DOWN_RIGHT: return horizontal_offset::FACING_DOWN_RIGHT;
      case CharacterMoveDirection::DOWN: return horizontal_offset::FACING_DOWN;
      case CharacterMoveDirection::DOWN_LEFT: return horizontal_offset::FACING_DOWN_RIGHT;
      case CharacterMoveDirection::LEFT: return horizontal_offset::FACING_RIGHT;
      default: return horizontal_offset::FACING_RIGHT;
    }
  }();
  const int vertical_multiplier = [&] {
    switch ( ct ) {
      case CharacterType::FIRE_HERO: return 16;
      case CharacterType::BLACK_HERO_WHITE_HORSE: return 9;
    }
  }();

  sf::Vector2<int> sprite_local_position{ HERO_SPRITE_WIDTH * horizontal_multiplier,
                                          HERO_SPRITE_HEIGHT * vertical_multiplier };
  sf::Vector2<int> sprite_crop_size{ HERO_SPRITE_WIDTH, HERO_SPRITE_HEIGHT };

  sf::Sprite cropped_sprite = cropTexture( heroes_sprite_texture, sprite_local_position, sprite_crop_size );
  switch ( cmd ) {
    case CharacterMoveDirection::UP_LEFT:
    case CharacterMoveDirection::LEFT:
    case CharacterMoveDirection::DOWN_LEFT: flipSpriteHorizontally( cropped_sprite );
    default:  // other directions have dedicated textures
  }
  return cropped_sprite;
}

// [[nodiscard]] sf::Sprite SpriteFactory ::getSpriteFromBinding( CastleUnitType ) noexcept {
// }

// [[nodiscard]] sf::Sprite SpriteFactory ::getSpriteFromBinding( ConfluxUnitType ) noexcept {
// }

// [[nodiscard]] sf::Sprite SpriteFactory ::getSpriteFromBinding( ForgeUnitType ) noexcept {
// }
