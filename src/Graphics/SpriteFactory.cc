#include "Graphics/SpriteFactory.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cstddef>
#include <cstdint>
#include <magic_enum/magic_enum.hpp>
#include <numeric>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>

#include "Artifact/ArtifactLib.h"
#include "Exceptions/Err.hpp"
#include "Miscellaneous/DiscardReturn.hpp"
#include "Miscellaneous/ProjectLib.h"
#include "Miscellaneous/ToLowerString.hpp"
#include "Unit/UnitsLib.h"

[[nodiscard]] sf::Sprite SpriteFactory::cropTexture( const sf::Texture& texture, sf::Vector2<int> ltc_pos,
                                                     sf::Vector2<int> size ) noexcept {
  return sf::Sprite{ texture, sf::IntRect{ ltc_pos, size } };
}

[[nodiscard]] sf::Texture SpriteFactory::loadTextureOrAbort( std::string_view path ) noexcept {
  sf::Texture t;
  err::passCondOrAbort( t.loadFromFile( path ), "couldn't load: ", path );
  return t;
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

[[nodiscard]] sf::Sprite SpriteFactory::getSpriteFromBinding( HexagonType ht ) noexcept {
  static constexpr std::string_view HEXAGON_FILES_LOCATION = "sprites/battle/aux/";
  const std::string filename = std::string{ HEXAGON_FILES_LOCATION } + [&] -> const char* {
    switch ( ht ) {
      case HexagonType::EMPTY: return "Hexagon";
      case HexagonType::ATTACK: return "Hexagon_Attack";
      case HexagonType::MOVE: return "Hexagon_Movement";
      case HexagonType::IN_ACTION: return "Hexagon_Unit_In_Action";
      case HexagonType::COUNT: std::unreachable();
    }
  }() + ".png";
  return sf::Sprite{ getTexture( ht, filename ) };
}

[[nodiscard]] sf::Sprite SpriteFactory::getSpriteFromBinding( ArtifactType at ) noexcept {
  static constexpr std::string_view ARTIFACT_SPRITE_FILE_LOCATION = "sprites/artifacts/artifacts.png";

  static constexpr int ARTIFACT_SPRITE_WIDTH = 58;
  static constexpr int ARTIFACT_SRPITE_HEIGHT = 64;

  static constexpr int HORIZONTAL_PADDING_PRE_COLUMN_0 = 8;
  static constexpr int HORIZONTAL_PADDING_MID_COLUMNS = 5;

  static constexpr std::array<int, 6> VERTICAL_PADDING_PRE_NTH_ROW = { 6, 5, 10, 15, 8, 4 };

  auto get_sprite_location_from_sprite_relative_pos = [&]( int column, int row ) {
    err::passCondOrAbort( column >= 0 && column <= 26, "column" );
    err::passCondOrAbort( row >= 0 && row <= 5, "row" );
    int horizontal_location =
        HORIZONTAL_PADDING_PRE_COLUMN_0 + ( column * ( ARTIFACT_SPRITE_WIDTH + HORIZONTAL_PADDING_MID_COLUMNS ) );

    int vertical_location =
        std::accumulate( VERTICAL_PADDING_PRE_NTH_ROW.begin(), VERTICAL_PADDING_PRE_NTH_ROW.begin() + row + 1, 0 )
        + ( row * ARTIFACT_SRPITE_HEIGHT );

    return sf::Vector2<int>( horizontal_location, vertical_location );
  };

  auto sprite_location = [&] -> sf::Vector2<int> {
    switch ( at ) {
      case ArtifactType::CROWN_OF_THE_SUPREME_MAGI: return get_sprite_location_from_sprite_relative_pos( 17, 0 );
      case ArtifactType::HELM_OF_THE_ALABASTER_UNICORN: return get_sprite_location_from_sprite_relative_pos( 14, 0 );
      case ArtifactType::THUNDER_HELMET: return get_sprite_location_from_sprite_relative_pos( 19, 0 );
      case ArtifactType::DRAGON_WING_TABARD: return get_sprite_location_from_sprite_relative_pos( 10, 1 );
      case ArtifactType::CAPE_OF_VELOCITY: return get_sprite_location_from_sprite_relative_pos( 16, 3 );
      case ArtifactType::NECKLACE_OF_DRAGONTEETH: return get_sprite_location_from_sprite_relative_pos( 11, 1 );
      case ArtifactType::CELESTIAL_NECKLACE_OF_BLISS: return get_sprite_location_from_sprite_relative_pos( 1, 1 );
      case ArtifactType::NECKLACE_OF_SWIFTNESS: return get_sprite_location_from_sprite_relative_pos( 14, 3 );
      case ArtifactType::CENTAURS_AXE: return get_sprite_location_from_sprite_relative_pos( 2, 0 );
      case ArtifactType::TITANS_GLADIUS: return get_sprite_location_from_sprite_relative_pos( 7, 0 );
      case ArtifactType::SWORD_OF_JUDGEMENT: return get_sprite_location_from_sprite_relative_pos( 3, 1 );
      case ArtifactType::SHIELD_OF_THE_DWARVEN_LORDS: return get_sprite_location_from_sprite_relative_pos( 8, 0 );
      case ArtifactType::DRAGON_SCALE_SHIELD: return get_sprite_location_from_sprite_relative_pos( 7, 1 );
      case ArtifactType::SENTINELS_SHIELD: return get_sprite_location_from_sprite_relative_pos( 13, 0 );
      case ArtifactType::RIB_CAGE: return get_sprite_location_from_sprite_relative_pos( 21, 0 );
      case ArtifactType::DRAGON_SCALE_ARMOR: return get_sprite_location_from_sprite_relative_pos( 8, 1 );
      case ArtifactType::TITANS_CUIRASS: return get_sprite_location_from_sprite_relative_pos( 25, 0 );
      case ArtifactType::QUIET_EYE_OF_THE_DRAGON: return get_sprite_location_from_sprite_relative_pos( 5, 1 );
      case ArtifactType::EQUESTRIAN_GLOVES: return get_sprite_location_from_sprite_relative_pos( 13, 2 );
      case ArtifactType::RING_OF_VITALITY: return get_sprite_location_from_sprite_relative_pos( 11, 3 );
      case ArtifactType::RING_OF_WAYFARER: return get_sprite_location_from_sprite_relative_pos( 12, 2 );
      case ArtifactType::RING_OF_LIFE: return get_sprite_location_from_sprite_relative_pos( 12, 3 );
      case ArtifactType::DRAGONBONE_GREAVES: return get_sprite_location_from_sprite_relative_pos( 9, 1 );
      case ArtifactType::SANDALS_OF_THE_SAINT: return get_sprite_location_from_sprite_relative_pos( 0, 1 );
      case ArtifactType::BOOTS_OF_SPEED: return get_sprite_location_from_sprite_relative_pos( 15, 3 );
      case ArtifactType::COUNT: std::unreachable();
    }
  }();

  return sf::Sprite{ getTexture( at, ARTIFACT_SPRITE_FILE_LOCATION ),
                     sf::IntRect{ sprite_location, { ARTIFACT_SPRITE_WIDTH, ARTIFACT_SRPITE_HEIGHT } } };
}

[[nodiscard]] sf::Sprite SpriteFactory::getSpriteFromBinding( Tagged<Terrain, SpriteDomain::WORLD> t ) noexcept {
  static constexpr std::string_view FILE_LOCATION = "sprites/terrain/";
  const std::string tex_filename = std::string{ FILE_LOCATION } + [&] -> const char* {
    switch ( t.val ) {
      case Terrain::GRASS: return "tgrb000";
      case Terrain::DIRT: return "tdtb000";
      case Terrain::MOSTLY_GRASS: return "tgrb022";
      case Terrain::ROCKS: return "trob000";
      case Terrain::ROCKS_CRUSHED: return "trob024";
      case Terrain::SAND: return "tsub000";
      case Terrain::COUNT: std::unreachable();
    }
  }() + ".png";
  err::passCondOrAbort( getTexture<Terrain, SpriteDomain::WORLD>( t.val, tex_filename ).getSize()
                        == sf::Vector2u{ 32, 32 } );
  return sf::Sprite{ getTexture<Terrain, SpriteDomain::WORLD>( t.val, tex_filename ) };
}

[[nodiscard]] sf::Sprite SpriteFactory::getSpriteFromBinding( Tagged<Terrain, SpriteDomain::BATTLE> t ) noexcept {
  static constexpr std::string_view FILE_LOCATION = "sprites/battle_backgrounds/";
  const std::string tex_filename = std::string{ FILE_LOCATION } + [&] -> const char* {
    // TODO find actual sprite names maybe
    switch ( t.val ) {
      case Terrain::GRASS:
      case Terrain::DIRT:
      case Terrain::MOSTLY_GRASS:
      case Terrain::ROCKS:
      case Terrain::ROCKS_CRUSHED:
      case Terrain::SAND: return "CmBkDrTr";
      case Terrain::COUNT: std::unreachable();
    }
  }() + ".png";
  return sf::Sprite{ getTexture<Terrain, SpriteDomain::BATTLE>( t.val, tex_filename ) };
}

[[nodiscard]] sf::Sprite SpriteFactory ::getSpriteFromBinding( CharacterType ct, CharacterMoveDirection cmd ) noexcept {
  static constexpr int HERO_SPRITE_WIDTH = 96;
  static constexpr int HERO_SPRITE_HEIGHT = 64;

  static constexpr std::string_view HEROES_SPRITES_FILE_PATH = "sprites/heroes_adventure.png";
  // std::cout << magic_enum::enum_name( ct ) << std::endl;
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
      case CharacterType::COUNT: err::passCondOrAbort( false, "COUNT" ); std::unreachable();
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
  sf::Sprite s2 = cropped_sprite;

  return cropped_sprite;
}

[[nodiscard]] sf::Sprite SpriteFactory ::getSpriteFromBinding( CastleUnitType cut ) noexcept {
  static constexpr std::string_view FILE_LOCATION = "sprites/units/castle/";
  const std::string tex_filename = std::string{ FILE_LOCATION } + toLower( magic_enum::enum_name( cut ) ) + ".png";

  auto crop = [cut] -> sf::Vector2<int> {
    switch ( cut ) {
      // TODO update widths to center the sprites
      case CastleUnitType::PIKEMAN: return { 62, 113 };
      case CastleUnitType::ARCHER: return { 70, 106 };  // x=115 for perfect swapping
      case CastleUnitType::GRIFFIN: return { 225, 134 };
      case CastleUnitType::SWORDSMAN: return { 50, 130 };
      case CastleUnitType::MONK: return { 74, 113 };
      case CastleUnitType::CAVALIER: return { 165, 153 };
      case CastleUnitType::ANGEL: return { 108, 108 };  // x=153 for perfect swapping sprites without offset
      case CastleUnitType::COUNT: std::unreachable();
    }
  }();

  return sf::Sprite{ getTexture( cut, tex_filename ), sf::IntRect{ { 0, 0 }, crop } };
}

[[nodiscard]] sf::Sprite SpriteFactory ::getSpriteFromBinding( ConfluxUnitType ) noexcept {
  err::passCondOrAbort( false, "not implemented" );
  std::unreachable();
}

[[nodiscard]] sf::Sprite SpriteFactory ::getSpriteFromBinding( ForgeUnitType ) noexcept {
  err::passCondOrAbort( false, "not implemented" );
  std::unreachable();
}

[[nodiscard]] sf::Sprite SpriteFactory::getSpriteFromBinding( WarMachineType ) noexcept {
  err::passCondOrAbort( false, "not implemented" );
  std::unreachable();
}

/* === @PUBLIC === */

void SpriteFactory::flipSpriteHorizontally( sf::Sprite& sprite ) noexcept {
  const float left_before = sprite.getGlobalBounds().position.x;
  sprite.scale( { -1.f, 1.f } );
  const float left_after = sprite.getGlobalBounds().position.x;
  sprite.move( { left_before - left_after, 0.f } );
}

[[nodiscard]] int SpriteFactory::getFootHeightForUnit( UnitTypeV type ) noexcept {
  return std::visit(
      [&]( const auto t ) {
        using T = std::decay_t<decltype( t )>;
        err::passCondOrAbort( t != T::COUNT, "t == T::COUNT" );
        static std::array<std::optional<int>, static_cast<size_t>( T::COUNT )> heights;
        auto index = static_cast<size_t>( t );
        if ( !heights[index].has_value() ) {
          heights[index] = [&] {
            const sf::Sprite s = SpriteFactory::getSpriteFromBinding( t );
            const sf::Texture& tex = s.getTexture();
            sf::IntRect rect = s.getTextureRect();

            sf::Image image = tex.copyToImage();

            for ( int y = rect.size.y - 1; y >= 0; --y ) {
              auto abs_y = static_cast<unsigned int>( rect.position.y + y );

              for ( int x = 0; x < rect.size.x; ++x ) {
                auto abs_x = static_cast<unsigned int>( rect.position.x + x );

                sf::Color pixel = image.getPixel( { abs_x, abs_y } );

                if ( pixel.a > 0 ) {
                  return y;
                }
              }
            }
            err::passCondOrAbort( false, "transparent image" );
            std::unreachable();
          }();
        }
        return *heights[index];
      },
      type );
}