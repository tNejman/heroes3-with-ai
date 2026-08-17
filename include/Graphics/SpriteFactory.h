#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <magic_enum/magic_enum.hpp>
#include <optional>
#include <string_view>
#include <type_traits>
#include <variant>

#include "Artifact/ArtifactLib.h"
#include "Exceptions/Err.hpp"
#include "Miscellaneous/EnumWithCount.hpp"
#include "Miscellaneous/ProjectLib.h"
#include "Unit/UnitsLib.h"

// using SpriteBinding = std::variant<Terrain, CharacterType, CastleUnitType, ConfluxUnitType, ForgeUnitType>;

enum class SpriteDomain : bool { WORLD, BATTLE };
template <EnumWithCount T, SpriteDomain D>
struct Tagged {
  T val;
};

enum class HexagonType : uint8_t { EMPTY, ATTACK, MOVE, IN_ACTION, COUNT };

class SpriteFactory {
  template <EnumWithCount Binding>
  static const sf::Texture& getTexture( Binding b, std::string_view path ) noexcept {
    static std::array<std::optional<sf::Texture>, static_cast<size_t>( Binding::COUNT )> lookup;

    err::passCondOrAbort( b != Binding::COUNT, "getTexture -> abort; type: ", magic_enum::enum_type_name<Binding>() );

    const auto index = static_cast<size_t>( b );
    if ( !lookup[index].has_value() ) {
      lookup[index] = loadTextureOrAbort( path );
    }
    return *lookup[index];
  }

  template <EnumWithCount Binding, SpriteDomain D>
  static const sf::Texture& getTexture( Binding b, std::string_view path ) noexcept {
    static std::array<std::optional<sf::Texture>, static_cast<size_t>( Binding::COUNT )> lookup;
    err::passCondOrAbort( b != Binding::COUNT );
    const auto index = static_cast<size_t>( b );
    if ( !lookup[index].has_value() ) {
      lookup[index] = loadTextureOrAbort( path );
    }
    return *lookup[index];
  }

  [[nodiscard]] static sf::Texture loadTextureOrAbort( std::string_view path ) noexcept;
  [[nodiscard]] static sf::Sprite cropTexture( const sf::Texture& texture, sf::Vector2<int> ltc_pos,
                                               sf::Vector2<int> size ) noexcept;

  static void eraseCharactersTextureCornerMarkers( sf::Texture&, unsigned int width, unsigned int height ) noexcept;

  [[nodiscard]] static sf::Sprite getSpriteFromBinding( HexagonType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( ArtifactType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( Tagged<Terrain, SpriteDomain::BATTLE> ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( Tagged<Terrain, SpriteDomain::WORLD> ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( CharacterType, CharacterMoveDirection ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( CastleUnitType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( ConfluxUnitType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( ForgeUnitType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( WarMachineType ) noexcept;

 public:
  SpriteFactory() = delete;

  static void flipSpriteHorizontally( sf::Sprite& ) noexcept;

  template <EnumWithCount T>
  [[nodiscard]] static sf::Sprite getSpriteFromBindingV( T binding ) noexcept {
    err::passCondOrAbort( binding != T::COUNT );
    return getSpriteFromBinding( binding );
  }
  template <Enum T1, Enum T2>
  [[nodiscard]] static sf::Sprite getSpriteFromBindingV( T1 binding1, T2 binding2 ) noexcept {
    return getSpriteFromBinding( binding1, binding2 );
  }

  template <EnumWithCount T, SpriteDomain D>
  [[nodiscard]] static sf::Sprite getSpriteFromBindingV( Tagged<T, D> binding ) noexcept {
    err::passCondOrAbort( binding.val != T::COUNT );
    return getSpriteFromBinding( binding );
  }

  [[nodiscard]] static sf::Sprite getSpriteFromBindingV( UnitTypeV type ) noexcept {
    return std::visit(
        [&]( const auto c_type ) {
          using T = std::decay_t<decltype( c_type )>;
          err::passCondOrAbort( c_type != T::COUNT, "UnitTypeV val was ::COUNT" );
          return getSpriteFromBinding( c_type );
        },
        type );
  }

  [[nodiscard]] static int getFootHeightForUnit( UnitTypeV type ) noexcept;
};