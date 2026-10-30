#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "engine/model/IGraphics/SpriteBinding.h"
#include "engine/model/IGraphics/TextureLoader.h"

class SpriteFactory {
 private:
 public:
  SpriteFactory() = delete;
  ~SpriteFactory() = default;
  SpriteFactory( const SpriteFactory& ) = delete;
  SpriteFactory( SpriteFactory&& ) = delete;
  SpriteFactory& operator=( const SpriteFactory& ) = default;
  SpriteFactory& operator=( SpriteFactory&& ) = delete;

  template <typename Object, typename GlobalState = game::IState, typename... Params>
  requires SpriteBound<Object, GlobalState, Params...>
  [[nodiscard]] static constexpr TextureSource source( const Object& object, Params... params ) noexcept {
    return ResolvedSpriteBinding<Object, GlobalState>::source( object, params... );
  }

  template <typename Object, typename GlobalState = game::IState, typename... Params>
  requires SpriteBound<Object, GlobalState, Params...>
  [[nodiscard]] static sf::Sprite make( const Object& object, Params... params ) noexcept {
    const TextureSource texture_source{ source<Object, GlobalState>( object, params... ) };
    const sf::Texture& texture = TextureLoader::getTexture( texture_source );

    if ( texture_source.crop_.has_value() ) {
      return sf::Sprite{ texture, *texture_source.crop_ };
    }
    return sf::Sprite{ texture };
  }

  static void flipSpriteHorizontally( sf::Sprite& ) noexcept;
};