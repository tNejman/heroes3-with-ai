#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "aux/DiscardReturn.hpp"
#include "engine/platform/Graphics/GraphicsLib.h"

namespace graphics {

inline void eraseCharactersTextureCornerMarkers( sf::Texture& texture ) noexcept {
  sf::Image image = texture.copyToImage();
  const sf::Vector2u size = image.getSize();
  for ( unsigned int y = HERO_SPRITE_HEIGHT - 1; y < size.y; y += HERO_SPRITE_HEIGHT ) {
    for ( unsigned int x = HERO_SPRITE_WIDTH - 1; x < size.x; x += HERO_SPRITE_WIDTH ) {
      image.setPixel( { x, y }, sf::Color::Transparent );
    }
  }
  DISCARD_RETURN() texture.loadFromImage( image );
}

inline void flipSpriteHorizontally( sf::Sprite& sprite ) noexcept {
  const float left_before = sprite.getGlobalBounds().position.x;
  sprite.scale( sf::Vector2f{ -1.F, 1.F } );
  const float left_after = sprite.getGlobalBounds().position.x;
  sprite.move( sf::Vector2f{ left_before - left_after, 0.F } );
}

};  // namespace graphics