#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <magic_enum/magic_enum.hpp>
#include <string_view>

#include "aux/Enum.hpp"
#include "core/Artifact/ArtifactLib.h"
#include "core/Misc/ProjectLib.h"
#include "core/Unit/UnitsLib.h"
#include "core/WorldMap/OverworldObstacle.h"

enum class SpriteDomain : char { WORLD, BATTLE };

template <Enum E, SpriteDomain D>
struct Tagged {
  E val;
};

enum class HexagonType : char { EMPTY, ATTACK, MOVE, IN_ACTION };

class SpriteFactory {  // NOLINT(cppcoreguidelines-special-member-functions)
 private:
  template <Enum Binding>
  static const sf::Texture& getTexture(
      Binding b, std::string_view path,
      const std::function<void( sf::Texture& )>& texutre_cleanup_func = nullptr ) noexcept;

  template <Enum Binding, SpriteDomain D>
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
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( artifact::Type ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( Tagged<Terrain, SpriteDomain::BATTLE> ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( Tagged<Terrain, SpriteDomain::WORLD> ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( OverworldObstacleType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( character::Type, CharacterMoveDirection ) noexcept;
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

  template <Enum Binding>
  [[nodiscard]] static inline sf::Sprite getSpriteFromBindingV( Binding binding ) noexcept;

  template <Enum Binding1, Enum Binding2>
  [[nodiscard]] static inline sf::Sprite getSpriteFromBindingV( Binding1 binding1, Binding2 binding2 ) noexcept;

  /**
   * @note use if enum has different meanings in different contexts
   */
  template <Enum Binding, SpriteDomain D>
  [[nodiscard]] static inline sf::Sprite getSpriteFromBindingV( Tagged<Binding, D> binding ) noexcept;

  [[nodiscard]] inline static sf::Sprite getSpriteFromBindingV( UnitTypeV type ) noexcept;

  [[nodiscard]] static int getFootHeightForUnit( UnitTypeV type ) noexcept;
};

#include "engine/Graphics/SpriteFactory.tpp"  // IWYU pragma: keep