#include "engine/model/IGraphics/TextureLoader.h"

#include <SFML/Graphics/Texture.hpp>
#include <string>

#include "aux/Err.hpp"
#include "aux/StringHash.hpp"
#include "engine/model/IGraphics/SpriteBinding.h"

[[nodiscard]] sf::Texture TextureLoader::loadTextureOrAbort( const std::string& path ) noexcept {
  sf::Texture t;
  err::passCondOrAbort( t.loadFromFile( path ), "couldn't load: ", path );
  return t;
}

[[nodiscard]] const sf::Texture& TextureLoader::getTexture( const TextureSource& texture_source ) noexcept {
  static StringMap<sf::Texture> lookup;
  const std::string full_file_path = texture_source.getFullPath();

  if ( !lookup.contains( full_file_path ) ) {
    lookup[full_file_path] = loadTextureOrAbort( full_file_path );
    lookup[full_file_path].setSmooth( false );
    if ( texture_source.tex_cleanup_fun_ != nullptr ) {
      texture_source.tex_cleanup_fun_( lookup[full_file_path] );
    }
  }

  return lookup[full_file_path];
}