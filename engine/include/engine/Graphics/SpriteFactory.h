#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <magic_enum/magic_enum.hpp>
#include <string_view>

#include "aux/EnumWithCount.hpp"
#include "core/Artifact/ArtifactLib.h"
#include "core/Misc/ProjectLib.h"
#include "core/Unit/UnitsLib.h"
#include "core/WorldMap/OverworldObstacle.h"

enum class SpriteDomain : char { WORLD, BATTLE };

template <EnumWithCount T, SpriteDomain D>
struct Tagged {
  T val;
};

enum class HexagonType : char { EMPTY, ATTACK, MOVE, IN_ACTION, COUNT };

class SpriteFactory {  // NOLINT(cppcoreguidelines-special-member-functions)
 private:
  template <EnumWithCount Binding>
  static const sf::Texture& getTexture(
      Binding b, std::string_view path,
      const std::function<void( sf::Texture& )>& texutre_cleanup_func = nullptr ) noexcept;

  template <EnumWithCount Binding, SpriteDomain D>
  static const sf::Texture& getTexture(
      Binding b, std::string_view path,
      const std::function<void( sf::Texture& )>& texutre_cleanup_func = nullptr ) noexcept;

  template <typename Binding>
  static const sf::Texture& getTexture(
      std::string_view path, const std::function<void( sf::Texture& )>& texutre_cleanup_func = nullptr ) noexcept;

  [[nodiscard]] static sf::Texture loadTextureOrAbort( std::string_view path ) noexcept;
  [[nodiscard]] static sf::Sprite cropTexture( const sf::Texture& texture, sf::Vector2<int> ltc_pos,
                                               sf::Vector2<int> size ) noexcept;

  static void eraseCharactersTextureCornerMarkers( sf::Texture&, unsigned int width, unsigned int height ) noexcept;
  static void cleanupRawMagentaAndCyanTexture( sf::Texture& ) noexcept;

  [[nodiscard]] static sf::Sprite getSpriteFromBinding( HexagonType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( ArtifactType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( Tagged<Terrain, SpriteDomain::BATTLE> ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( Tagged<Terrain, SpriteDomain::WORLD> ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( OverworldObstacleType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( CharacterType, CharacterMoveDirection ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( CastleUnitType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( ConfluxUnitType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( ForgeUnitType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( WarMachineType ) noexcept;

 public:
  SpriteFactory() = delete;
  SpriteFactory( const SpriteFactory& ) = delete;
  SpriteFactory( SpriteFactory&& ) = delete;
  SpriteFactory& operator=( const SpriteFactory& ) = delete;
  SpriteFactory& operator=( SpriteFactory&& ) = delete;

  static void flipSpriteHorizontally( sf::Sprite& ) noexcept;

  template <EnumWithCount T>
  [[nodiscard]] static inline sf::Sprite getSpriteFromBindingV( T binding ) noexcept;

  template <Enum T1, Enum T2>
  [[nodiscard]] static inline sf::Sprite getSpriteFromBindingV( T1 binding1, T2 binding2 ) noexcept;

  template <EnumWithCount T, SpriteDomain D>
  [[nodiscard]] static inline sf::Sprite getSpriteFromBindingV( Tagged<T, D> binding ) noexcept;

  [[nodiscard]] inline static sf::Sprite getSpriteFromBindingV( UnitTypeV type ) noexcept;
  [[nodiscard]] static int getFootHeightForUnit( UnitTypeV type ) noexcept;
};

#include "engine/Graphics/SpriteFactory.tpp"  // IWYU pragma: keep
