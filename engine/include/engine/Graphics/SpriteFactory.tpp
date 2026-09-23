#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <array>
#include <cstddef>
#include <functional>
#include <optional>
#include <string_view>
#include <type_traits>
#include <variant>

#include "aux/Enum.hpp"
#include "aux/Err.hpp"
#include "core/Unit/UnitsLib.h"
#include "engine/Graphics/SpriteFactory.h"

/* ==== @PRIVATE ==== */

template <Enum Binding>
const sf::Texture& SpriteFactory::getTexture(
    Binding b, std::string_view path, const std::function<void( sf::Texture& )>& texutre_cleanup_func ) noexcept {
  static std::array<std::optional<sf::Texture>, static_cast<size_t>( magic_enum::enum_count<Binding>() )> lookup;
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

template <Enum Binding, SpriteDomain D>
const sf::Texture& SpriteFactory::getTexture(
    Binding b, std::string_view path, const std::function<void( sf::Texture& )>& texutre_cleanup_func ) noexcept {
  static std::array<std::optional<sf::Texture>, static_cast<size_t>( magic_enum::enum_count<Binding>() )> lookup;
  const auto index = static_cast<size_t>( b );
  if ( !lookup[index].has_value() ) {
    lookup[index] = loadTextureOrAbort( path );
    if ( texutre_cleanup_func ) {
      texutre_cleanup_func( *lookup[index] );
    }
  }
  return *lookup[index];
}

template <typename Binding>
const sf::Texture& SpriteFactory::getTexture(
    std::string_view path, const std::function<void( sf::Texture& )>& texutre_cleanup_func ) noexcept {
  static const sf::Texture texture = [&] {
    sf::Texture t;
    t = loadTextureOrAbort( path );
    if ( texutre_cleanup_func ) {
      texutre_cleanup_func( t );
    }
    return t;
  }();
  return texture;
}

/* ==== @PUBLIC ==== */

template <Enum Binding>
[[nodiscard]] inline sf::Sprite SpriteFactory::getSpriteFromBindingV( Binding binding ) noexcept {
  return getSpriteFromBinding( binding );
}
template <Enum Binding1, Enum Binding2>
[[nodiscard]] inline sf::Sprite SpriteFactory::getSpriteFromBindingV( Binding1 binding1, Binding2 binding2 ) noexcept {
  return getSpriteFromBinding( binding1, binding2 );
}

template <Enum Binding, SpriteDomain D>
[[nodiscard]] inline sf::Sprite SpriteFactory::getSpriteFromBindingV( Tagged<Binding, D> binding ) noexcept {
  return getSpriteFromBinding( binding );
}

[[nodiscard]] inline sf::Sprite SpriteFactory::getSpriteFromBindingV( UnitTypeV type ) noexcept {
  return std::visit( [&]( const auto c_type ) { return getSpriteFromBinding( c_type ); }, type );
}