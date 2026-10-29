#include "engine/platform/Graphics/SpriteVisitor.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <optional>
#include <string>
#include <utility>

#include "aux/Err.hpp"
#include "aux/StringHash.hpp"
#include "core/Artifact/Artifact.h"
#include "core/Battle/Battle.h"
#include "core/Battle/Obstacle.hpp"
#include "core/Character/Character.h"
#include "core/Magic/Spell.h"
#include "core/Resource/Resource.h"
#include "core/WorldMap/OverworldObstacle.h"
#include "engine/model/IGraphics/SpriteBinding.h"
#include "engine/model/IGraphics/Visitor.h"
#include "engine/platform/Graphics/SpriteFactory.h"

[[nodiscard]] sf::Texture SpriteVisitor::loadTextureOrAbort( const std::string& path ) noexcept {
  sf::Texture t;
  err::passCondOrAbort( t.loadFromFile( path ), "couldn't load: ", path );
  return t;
}

const sf::Texture& SpriteVisitor::getTexture( const TextureSource& texture_source ) noexcept {
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

sf::Sprite SpriteVisitor::getSprite( const sf::Texture& texture, const TextureSource& texture_source ) noexcept {
  sf::Sprite sprite = [&] {
    if ( texture_source.crop_.has_value() ) {
      return sf::Sprite{ texture, *texture_source.crop_ };
    }
    return sf::Sprite{ texture };
  }();

  if ( texture_source.sprite_cleanup_fun_ != nullptr ) {
    texture_source.sprite_cleanup_fun_( sprite );
  }

  return sprite;
}

void SpriteVisitor::visit( const Artifact& e ) {
  // sprite_ = SpriteFactory::getSpriteFromBindingV( e.getData().type_ );
}

void SpriteVisitor::visit( const Obstacle& ) {
  err::passCondOrAbort( false, "not implemented: OBSTACLE" );
}

void SpriteVisitor::visit( const Character& e ) {
  sprite_ = SpriteFactory::getSpriteFromBindingV( e.getType(), e.getOrientation() );
}

void SpriteVisitor::visit( const Spell& ) {
  err::passCondOrAbort( false, "not implemented: SPELL" );
}

void SpriteVisitor::visit( const Resource& ) {
  err::passCondOrAbort( false, "not implemented: RESOURCE" );
}

void SpriteVisitor::visit( const OverworldObstacle& e ) {
  sprite_ = SpriteFactory::getSpriteFromBindingV( e.getType() );
}

void SpriteVisitor::visit( const Building& ) {
  err::passCondOrAbort( false, "not implemented: BUILDING" );
}

void SpriteVisitor::visit( const UnitStack& e ) {
  sprite_ = SpriteFactory::getSpriteFromBindingV( e.getData().type_ );
}

sf::Sprite SpriteVisitor::extractSprite() noexcept {
  sf::Sprite moved_sprite = std::move( *sprite_ );
  sprite_ = std::nullopt;
  return moved_sprite;
}
