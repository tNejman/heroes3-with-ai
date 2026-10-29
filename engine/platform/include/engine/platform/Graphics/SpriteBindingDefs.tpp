#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <magic_enum/magic_enum.hpp>
#include <numeric>
#include <utility>
#include <variant>

#include "aux/Err.hpp"
#include "aux/ToLowerString.hpp"
#include "core/Artifact/Artifact.h"
#include "core/Artifact/ArtifactLib.h"
#include "core/Character/Character.h"
#include "core/Game/StateBattle.h"
#include "core/Game/StateOverworld.h"
#include "core/Misc/ProjectLib.h"
#include "core/Unit/UnitStack.h"
#include "core/Unit/UnitsLib.h"
#include "core/WorldMap/OverworldObstacle.h"
#include "engine/model/IGraphics/SpriteBinding.h"
#include "engine/platform/Graphics/GraphicsHelperFunctions.hpp"
#include "engine/platform/Graphics/GraphicsLib.h"
#include "engine/platform/Graphics/SpriteBindingDefs.h"  // IWYU pragma: keep
#include "engine/platform/Graphics/SpriteFactory.h"

[[nodiscard]] TextureSource SpriteBinding<HexagonType, game::StateBattle>::source( HexagonType hexagon_type ) noexcept {
  static TextureSource texture_source{ .path_prefix_ = SPRITE_ROOT_DIR + "/battle/aux/" };

  switch ( hexagon_type ) {
    case HexagonType::EMPTY: texture_source.path_ = "Hexagon"; break;
    case HexagonType::ATTACK: texture_source.path_ = "Hexagon_Attack"; break;
    case HexagonType::MOVE: texture_source.path_ = "Hexagon_Movement"; break;
    case HexagonType::IN_ACTION: texture_source.path_ = "Hexagon_Unit_In_Action"; break;
    default: err::abort( "invalid hex type" );
  }

  return texture_source;
}

[[nodiscard]] TextureSource SpriteBinding<Artifact>::source( artifact::Type artifact_type ) noexcept {
  static TextureSource texture_source{ .path_ = SPRITE_ROOT_DIR + "/artifacts/artifacts" };

  static constexpr int ARTIFACT_SPRITE_WIDTH = 58;
  static constexpr int ARTIFACT_SRPITE_HEIGHT = 64;

  static constexpr int HORIZONTAL_PADDING_PRE_COLUMN_0 = 8;
  static constexpr int HORIZONTAL_PADDING_MID_COLUMNS = 5;

  static constexpr std::array<int, 6> VERTICAL_PADDING_PRE_NTH_ROW = { 6, 5, 10, 15, 8, 4 };

  static constexpr int MIN_ARTIFACT_FILE_COLUMN_ID = 0;
  static constexpr int MAX_ARTIFACT_FILE_COLUMN_ID = 26;
  static constexpr int MIN_ARTIFACT_FILE_ROW_ID = 0;
  static constexpr int MAX_ARTIFACT_FILE_ROW_ID = 5;

  auto get_sprite_location_from_sprite_relative_pos = [&]( int column, int row ) -> sf::Vector2<int> {
    err::passCondOrAbort( column >= MIN_ARTIFACT_FILE_COLUMN_ID && column <= MAX_ARTIFACT_FILE_COLUMN_ID, "column" );
    err::passCondOrAbort( row >= MIN_ARTIFACT_FILE_ROW_ID && row <= MAX_ARTIFACT_FILE_ROW_ID, "row" );
    int horizontal_location =
        HORIZONTAL_PADDING_PRE_COLUMN_0 + ( column * ( ARTIFACT_SPRITE_WIDTH + HORIZONTAL_PADDING_MID_COLUMNS ) );

    int vertical_location =
        std::accumulate( VERTICAL_PADDING_PRE_NTH_ROW.begin(), VERTICAL_PADDING_PRE_NTH_ROW.begin() + row + 1, 0 )
        + ( row * ARTIFACT_SRPITE_HEIGHT );

    return { horizontal_location, vertical_location };
  };

  auto sprite_location = [&] -> sf::Vector2<int> {
    switch ( artifact_type ) {
      case artifact::Type::CROWN_OF_THE_SUPREME_MAGI: return get_sprite_location_from_sprite_relative_pos( 17, 0 );
      case artifact::Type::HELM_OF_THE_ALABASTER_UNICORN: return get_sprite_location_from_sprite_relative_pos( 14, 0 );
      case artifact::Type::THUNDER_HELMET: return get_sprite_location_from_sprite_relative_pos( 19, 0 );
      case artifact::Type::DRAGON_WING_TABARD: return get_sprite_location_from_sprite_relative_pos( 10, 1 );
      case artifact::Type::CAPE_OF_VELOCITY: return get_sprite_location_from_sprite_relative_pos( 16, 3 );
      case artifact::Type::NECKLACE_OF_DRAGONTEETH: return get_sprite_location_from_sprite_relative_pos( 11, 1 );
      case artifact::Type::CELESTIAL_NECKLACE_OF_BLISS: return get_sprite_location_from_sprite_relative_pos( 1, 1 );
      case artifact::Type::NECKLACE_OF_SWIFTNESS: return get_sprite_location_from_sprite_relative_pos( 14, 3 );
      case artifact::Type::CENTAURS_AXE: return get_sprite_location_from_sprite_relative_pos( 2, 0 );
      case artifact::Type::TITANS_GLADIUS: return get_sprite_location_from_sprite_relative_pos( 7, 0 );
      case artifact::Type::SWORD_OF_JUDGEMENT: return get_sprite_location_from_sprite_relative_pos( 3, 1 );
      case artifact::Type::SHIELD_OF_THE_DWARVEN_LORDS: return get_sprite_location_from_sprite_relative_pos( 8, 0 );
      case artifact::Type::DRAGON_SCALE_SHIELD: return get_sprite_location_from_sprite_relative_pos( 7, 1 );
      case artifact::Type::SENTINELS_SHIELD: return get_sprite_location_from_sprite_relative_pos( 13, 0 );
      case artifact::Type::RIB_CAGE: return get_sprite_location_from_sprite_relative_pos( 21, 0 );
      case artifact::Type::DRAGON_SCALE_ARMOR: return get_sprite_location_from_sprite_relative_pos( 8, 1 );
      case artifact::Type::TITANS_CUIRASS: return get_sprite_location_from_sprite_relative_pos( 25, 0 );
      case artifact::Type::QUIET_EYE_OF_THE_DRAGON: return get_sprite_location_from_sprite_relative_pos( 5, 1 );
      case artifact::Type::EQUESTRIAN_GLOVES: return get_sprite_location_from_sprite_relative_pos( 13, 2 );
      case artifact::Type::RING_OF_VITALITY: return get_sprite_location_from_sprite_relative_pos( 11, 3 );
      case artifact::Type::RING_OF_WAYFARER: return get_sprite_location_from_sprite_relative_pos( 12, 2 );
      case artifact::Type::RING_OF_LIFE: return get_sprite_location_from_sprite_relative_pos( 12, 3 );
      case artifact::Type::DRAGONBONE_GREAVES: return get_sprite_location_from_sprite_relative_pos( 9, 1 );
      case artifact::Type::SANDALS_OF_THE_SAINT: return get_sprite_location_from_sprite_relative_pos( 0, 1 );
      case artifact::Type::BOOTS_OF_SPEED: return get_sprite_location_from_sprite_relative_pos( 15, 3 );
    }
    err::abort( "requested rendering an artifact with no preset texture" );
  }();

  texture_source.crop_ = sf::IntRect{ sprite_location, { ARTIFACT_SPRITE_WIDTH, ARTIFACT_SRPITE_HEIGHT } };

  return texture_source;
}

[[nodiscard]] TextureSource SpriteBinding<Terrain, game::StateOverworld>::source( Terrain terrain ) noexcept {
  static TextureSource texture_source{ .path_prefix_ = SPRITE_ROOT_DIR + "/terrain/bg/" };

  texture_source.path_ = [&] {
    switch ( terrain ) {
      case Terrain::GRASS: return "tgrb000";
      case Terrain::DIRT: return "tdtb000";
      case Terrain::MOSTLY_GRASS: return "tgrb022";
      case Terrain::ROCKS: return "trob000";
      case Terrain::ROCKS_CRUSHED: return "trob024";
      case Terrain::SAND: return "tsub000";
    }
    err::abort( "unknown terrain type requested to render" );
  }();

  return texture_source;
}

[[nodiscard]] TextureSource SpriteBinding<Terrain, game::StateBattle>::source( Terrain terrain ) noexcept {
  static TextureSource texture_source{ .path_prefix_ = SPRITE_ROOT_DIR + "/battle_backgrounds/" };
  texture_source.path_ = [&] {
    // TODO find actual sprite names maybe
    switch ( terrain ) {
      case Terrain::GRASS:
      case Terrain::DIRT:
      case Terrain::MOSTLY_GRASS:
      case Terrain::ROCKS:
      case Terrain::ROCKS_CRUSHED:
      case Terrain::SAND: return "CmBkDrTr";
    }
    err::abort( "unknown terrain type requested to render" );
  }();

  return texture_source;
}

[[nodiscard]] TextureSource SpriteBinding<OverworldObstacle, game::StateOverworld>::source(
    OverworldObstacleType overworld_obstacle_type ) noexcept {
  static TextureSource texture_source{ .path_prefix_ = SPRITE_ROOT_DIR + "/landscape/" };
  texture_source.path_ = [&] {
    switch ( overworld_obstacle_type ) {
      case OverworldObstacleType::DRIED_TREE: return "AVLtRo06";
      case OverworldObstacleType::GREEN_TREE: return "AVLswt15";
    }
    err::abort( "unknown overworld obstacle type requested to render" );
  }();

  return texture_source;
}

[[nodiscard]] TextureSource SpriteBinding<Character, game::StateOverworld>::source(
    const Character& character ) noexcept {
  static TextureSource texture_source{ .path_prefix_ = SPRITE_ROOT_DIR + "/heroes_adventure",
                                       .tex_cleanup_fun_ = graphics::eraseCharactersTextureCornerMarkers };

  enum horizontal_offset : char {
    FACING_DOWN = 0,
    FACING_DOWN_RIGHT = 1,
    FACING_RIGHT = 2,
    FACING_UP_RIGHT = 3,
    FACING_UP = 4
  };

  const int horizontal_multiplier = [&] {
    switch ( character.getOrientation() ) {
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
    }
    err::abort( "unknown CharacerMoveDirection type requested to render" );
  }();
  const int vertical_multiplier = [&] {
    switch ( character.getType() ) {
      case character::Type::FIRE_HERO: return 16;
      case character::Type::BLACK_HERO_WHITE_HORSE: return 9;
    }
    err::abort( "requested rendering an unknown character::Type" );
  }();

  sf::Vector2<int> sprite_local_position{ graphics::HERO_SPRITE_WIDTH * horizontal_multiplier,
                                          graphics::HERO_SPRITE_HEIGHT * vertical_multiplier };
  sf::Vector2<int> sprite_crop_size{ graphics::HERO_SPRITE_WIDTH, graphics::HERO_SPRITE_HEIGHT };

  texture_source.crop_ = sf::IntRect{ sprite_local_position, sprite_crop_size };

  switch ( character.getOrientation() ) {
    case CharacterMoveDirection::UP_LEFT:
    case CharacterMoveDirection::LEFT:
    case CharacterMoveDirection::DOWN_LEFT: texture_source.sprite_cleanup_fun_ = graphics::flipSpriteHorizontally;
    default: texture_source.sprite_cleanup_fun_ = nullptr;  // other directions have dedicated textures
  }

  return texture_source;
}

[[nodiscard]] TextureSource SpriteBinding<UnitStack, game::StateBattle>::source( CastleUnitType unit_type ) noexcept {
  static TextureSource texture_source{ .path_prefix_ = SPRITE_ROOT_DIR + "/units/castle/" };
  texture_source.path_ = toLower( magic_enum::enum_name( unit_type ) );

  auto crop = [unit_type] -> sf::Vector2<int> {
    switch ( unit_type ) {
      // TODO update widths to center the sprites
      case CastleUnitType::PIKEMAN: return { 62, 113 };
      case CastleUnitType::ARCHER: return { 70, 106 };  // x=115 for perfect swapping
      case CastleUnitType::GRIFFIN: return { 225, 134 };
      case CastleUnitType::SWORDSMAN: return { 50, 130 };
      case CastleUnitType::MONK: return { 74, 113 };
      case CastleUnitType::CAVALIER: return { 165, 153 };
      case CastleUnitType::ANGEL: return { 108, 108 };  // x=153 for perfect swapping sprites without offset
    }
    err::abort( "unknown Castle Unit type requested to render" );
  }();

  texture_source.crop_ = sf::IntRect{ graphics::DEFAULT_CROP_LOCATION, crop };

  return texture_source;
}
[[nodiscard]] TextureSource SpriteBinding<UnitStack, game::StateBattle>::source( ConfluxUnitType unit_type ) noexcept {
  err::passCondOrAbort( false, "not implemented" );
  std::unreachable();
}
[[nodiscard]] TextureSource SpriteBinding<UnitStack, game::StateBattle>::source( ForgeUnitType unit_type ) noexcept {
  err::passCondOrAbort( false, "not implemented" );
  std::unreachable();
}
[[nodiscard]] TextureSource SpriteBinding<UnitStack, game::StateBattle>::source( WarMachineType unit_type ) noexcept {
  err::passCondOrAbort( false, "not implemented" );
  std::unreachable();
}
[[nodiscard]] TextureSource SpriteBinding<UnitStack, game::StateBattle>::source(
    const UnitStack& unit_stack ) noexcept {
  return std::visit( [&]( const auto& concrete_unit_type ) { return source( concrete_unit_type ); },
                     unit_stack.getData().type_ );
}
