#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

#include "engine/model/IGraphics/SpriteBinding.h"
class TextureLoader {
 private:
  [[nodiscard]] static sf::Texture loadTextureOrAbort( const std::string& path ) noexcept;

 public:
  TextureLoader() = delete;
  ~TextureLoader() = default;
  TextureLoader( const TextureLoader& ) = delete;
  TextureLoader( TextureLoader&& ) = delete;
  TextureLoader& operator=( const TextureLoader& ) = default;
  TextureLoader& operator=( TextureLoader&& ) = delete;

  [[nodiscard]] static const sf::Texture& getTexture( const TextureSource& texture_source ) noexcept;
};