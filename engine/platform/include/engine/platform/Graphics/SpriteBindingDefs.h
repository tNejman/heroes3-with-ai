#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

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
#include "engine/platform/Graphics/SpriteFactory.h"

static const inline std::string SPRITE_ROOT_DIR = "assets/sprites";

template <>
struct SpriteBinding<HexagonType, game::StateBattle> {
  [[nodiscard]] static TextureSource source( HexagonType hexagon_type ) noexcept;
};

template <>
struct SpriteBinding<Artifact> {
  [[nodiscard]] static TextureSource source( artifact::Type artifact_type ) noexcept;
};

template <>
struct SpriteBinding<Terrain, game::StateOverworld> {
  [[nodiscard]] static TextureSource source( Terrain terrain ) noexcept;
};

template <>
struct SpriteBinding<Terrain, game::StateBattle> {
  [[nodiscard]] static TextureSource source( Terrain terrain ) noexcept;
};

template <>
struct SpriteBinding<OverworldObstacle, game::StateOverworld> {
  [[nodiscard]] static TextureSource source( OverworldObstacleType overworld_obstacle_type ) noexcept;
};

template <>
struct SpriteBinding<Character, game::StateOverworld> {
  [[nodiscard]] static TextureSource source( const Character& character ) noexcept;
};

template <>
struct SpriteBinding<UnitStack, game::StateBattle> {
  [[nodiscard]] static TextureSource source( CastleUnitType unit_type ) noexcept;
  [[nodiscard]] static TextureSource source( ConfluxUnitType unit_type ) noexcept;
  [[nodiscard]] static TextureSource source( ForgeUnitType unit_type ) noexcept;
  [[nodiscard]] static TextureSource source( WarMachineType unit_type ) noexcept;

  [[nodiscard]] static TextureSource source( const UnitStack& unit_stack ) noexcept;
};

#include "engine/platform/Graphics/SpriteBindingDefs.tpp"  // IWYU pragma: keep