#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cstddef>
#include <optional>
#include <type_traits>
#include <utility>
#include <variant>

#include "aux/DiscardReturn.hpp"
#include "aux/Err.hpp"
#include "core/Game/StateBattle.h"
#include "core/Unit/UnitStack.h"
#include "engine/model/IGraphics/ISpriteFactory.h"
#include "engine/platform/Graphics/GraphicsLib.h"
#include "engine/platform/Graphics/SpriteBindingDefs.h"

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

[[nodiscard]] inline int getFootHeightForUnit( const UnitStack& unit_stack ) noexcept {
  return std::visit(
      [&]( const auto t ) {
        using T = std::decay_t<decltype( t )>;
        static std::array<std::optional<int>, magic_enum::enum_count<T>()> heights;
        auto index = static_cast<size_t>( t );
        if ( !heights[index].has_value() ) {
          heights[index] = [&] {
            const sf::Sprite s = SpriteFactory::make<UnitStack, game::StateBattle>( unit_stack );
            const sf::Texture& tex = s.getTexture();
            sf::IntRect rect = s.getTextureRect();

            sf::Image image = tex.copyToImage();

            for ( int y = rect.size.y - 1; y >= 0; --y ) {
              auto abs_y = static_cast<unsigned int>( rect.position.y + y );

              for ( int x = 0; x < rect.size.x; ++x ) {
                auto abs_x = static_cast<unsigned int>( rect.position.x + x );

                sf::Color pixel = image.getPixel( { abs_x, abs_y } );

                if ( pixel.a > 0 ) {
                  return y;
                }
              }
            }
            err::passCondOrAbort( false, "transparent image" );
            std::unreachable();
          }();
        }
        return *heights[index];
      },
      unit_stack.getData().type_ );
}

};  // namespace graphics