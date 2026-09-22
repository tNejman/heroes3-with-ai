#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "aux/Err.hpp"
#include "engine/Graphics/SpriteFactory.h"

/* ==== @PRIVATE ==== */

template <EnumWithCount Binding>
const sf::Texture& SpriteFactory::getTexture(
    Binding b, std::string_view path, const std::function<void( sf::Texture& )>& texutre_cleanup_func ) noexcept {
  static std::array<std::optional<sf::Texture>, static_cast<size_t>( Binding::COUNT )> lookup;

  err::passCondOrAbort( b != Binding::COUNT, "getTexture -> abort; type: ", magic_enum::enum_type_name<Binding>() );

  const auto index = static_cast<size_t>( b );
  if ( !lookup[index].has_value() ) {
    lookup[index] = loadTextureOrAbort( path );
    ( *lookup[index] ).setSmooth( false );
    if ( texutre_cleanup_func ) {
      texutre_cleanup_func( *lookup[index] );
    }
  }
  return *lookup[index];
}

template <EnumWithCount Binding, SpriteDomain D>
const sf::Texture& SpriteFactory::getTexture(
    Binding b, std::string_view path, const std::function<void( sf::Texture& )>& texutre_cleanup_func ) noexcept {
  static std::array<std::optional<sf::Texture>, static_cast<size_t>( Binding::COUNT )> lookup;

  err::passCondOrAbort( b != Binding::COUNT );

  const auto index = static_cast<size_t>( b );
  if ( !lookup[index].has_value() ) {
    lookup[index] = loadTextureOrAbort( path );
    if ( texutre_cleanup_func ) {
      texutre_cleanup_func( *lookup[index] );
    }
  }
  return *lookup[index];
}

/* ==== @PUBLIC ==== */

template <EnumWithCount T>
[[nodiscard]] inline sf::Sprite SpriteFactory::getSpriteFromBindingV( T binding ) noexcept {
  err::passCondOrAbort( binding != T::COUNT );
  return getSpriteFromBinding( binding );
}
template <Enum T1, Enum T2>
[[nodiscard]] inline sf::Sprite SpriteFactory::getSpriteFromBindingV( T1 binding1, T2 binding2 ) noexcept {
  return getSpriteFromBinding( binding1, binding2 );
}

template <EnumWithCount T, SpriteDomain D>
[[nodiscard]] inline sf::Sprite SpriteFactory::getSpriteFromBindingV( Tagged<T, D> binding ) noexcept {
  err::passCondOrAbort( binding.val != T::COUNT );
  return getSpriteFromBinding( binding );
}

[[nodiscard]] inline sf::Sprite SpriteFactory::getSpriteFromBindingV( UnitTypeV type ) noexcept {
  return std::visit(
      [&]( const auto c_type ) {
        using T = std::decay_t<decltype( c_type )>;
        err::passCondOrAbort( c_type != T::COUNT, "UnitTypeV val was ::COUNT" );
        return getSpriteFromBinding( c_type );
      },
      type );
}