#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "engine/model/IGraphics/SpriteBinding.h"

class SpriteFactory {
 private:
 public:
  SpriteFactory() = delete;
  ~SpriteFactory() = default;
  SpriteFactory( const SpriteFactory& ) = delete;
  SpriteFactory( SpriteFactory&& ) = delete;
  SpriteFactory& operator=( const SpriteFactory& ) = default;
  SpriteFactory& operator=( SpriteFactory&& ) = delete;

  template <typename Object, typename GlobalState = DefaultGlobalState, typename... Params>
  requires SpriteBound<Object, GlobalState, Params...>
  [[nodiscard]] static constexpr TextureSource source( Params... params ) noexcept {
    return ResolvedSpriteBinding<Object, GlobalState>::source( params... );
  }

  template <typename Object, typename GlobalState = DefaultGlobalState, typename... Params>
  requires SpriteBound<Object, GlobalState, Params...>
  [[nodiscard]] static sf::Sprite make( Params... params ) noexcept {
    const TextureSource texture_source{ source<Object, GlobalState>( params... ) };
    const sf::Texture& texture = TextureCache::get( texture_source.path_, texture_source.tex_cleanup_fun_ );

    if ( texture_source.crop_.has_value() ) {
      return sf::Sprite{ texture, *texture_source.crop_ };
    }
    return sf::Sprite{ texture };
  }

  static void flipSpriteHorizontally( sf::Sprite& ) noexcept;
};