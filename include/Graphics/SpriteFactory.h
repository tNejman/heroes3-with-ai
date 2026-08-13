#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <string_view>

#include "Miscellaneous/ProjectLib.h"
#include "Unit/UnitsLib.h"

// using SpriteBinding = std::variant<Terrain, CharacterType, CastleUnitType, ConfluxUnitType, ForgeUnitType>;

class SpriteFactory {
  [[nodiscard]] static sf::Texture loadTextureOrAbort( std::string_view path ) noexcept;
  [[nodiscard]] static sf::Sprite cropTexture( const sf::Texture& texture, sf::Vector2<int> ltc_pos,
                                               sf::Vector2<int> size ) noexcept;
  static void flipSpriteHorizontally( sf::Sprite& ) noexcept;

  static void eraseCharactersTextureCornerMarkers( sf::Texture&, unsigned int width, unsigned int height ) noexcept;

 public:
  SpriteFactory() = delete;

  [[nodiscard]] static sf::Sprite getSpriteFromBinding( Terrain ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( CharacterType, CharacterMoveDirection ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( CastleUnitType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( ConfluxUnitType ) noexcept;
  [[nodiscard]] static sf::Sprite getSpriteFromBinding( ForgeUnitType ) noexcept;
};