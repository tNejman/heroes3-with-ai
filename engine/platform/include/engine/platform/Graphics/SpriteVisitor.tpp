#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <concepts>
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
#include "engine/model/IGraphics/ISpriteFactory.h"
#include "engine/model/IGraphics/SpriteBinding.h"
#include "engine/model/IGraphics/Visitor.h"
#include "engine/platform/Graphics/SpriteFactory.h"
#include "engine/platform/Graphics/SpriteVisitor.h"

template <typename GameState>
requires std::derived_from<GameState, game::IState>
void SpriteVisitor<GameState>::visit( const Artifact& e ) {
  // sprite_ = SpriteFactory::getSpriteFromBindingV( e.getData().type_ );
  sprite_ = SpriteFactory::make<Artifact, GameState>( e );
}

template <typename GameState>
requires std::derived_from<GameState, game::IState>
void SpriteVisitor<GameState>::visit( const Obstacle& ) {
  err::passCondOrAbort( false, "not implemented: OBSTACLE" );
}

template <typename GameState>
requires std::derived_from<GameState, game::IState>
void SpriteVisitor<GameState>::visit( const Character& e ) {
  sprite_ = SpriteFactory::getSpriteFromBindingV( e.getType(), e.getOrientation() );
}

template <typename GameState>
requires std::derived_from<GameState, game::IState>
void SpriteVisitor<GameState>::visit( const Spell& ) {
  err::passCondOrAbort( false, "not implemented: SPELL" );
}

template <typename GameState>
requires std::derived_from<GameState, game::IState>
void SpriteVisitor<GameState>::visit( const Resource& ) {
  err::passCondOrAbort( false, "not implemented: RESOURCE" );
}

template <typename GameState>
requires std::derived_from<GameState, game::IState>
void SpriteVisitor<GameState>::visit( const OverworldObstacle& e ) {
  sprite_ = SpriteFactory::getSpriteFromBindingV( e.getType() );
}

template <typename GameState>
requires std::derived_from<GameState, game::IState>
void SpriteVisitor<GameState>::visit( const Building& ) {
  err::passCondOrAbort( false, "not implemented: BUILDING" );
}

template <typename GameState>
requires std::derived_from<GameState, game::IState>
void SpriteVisitor<GameState>::visit( const UnitStack& e ) {
  sprite_ = SpriteFactory::getSpriteFromBindingV( e.getData().type_ );
}

template <typename GameState>
requires std::derived_from<GameState, game::IState>
sf::Sprite SpriteVisitor<GameState>::extractSprite() noexcept {
  sf::Sprite moved_sprite = std::move( *sprite_ );
  sprite_ = std::nullopt;
  return moved_sprite;
}

// TextureSource SpriteVisitor::extractTextureSource() noexcept {
//   TextureSource moved_texture_source = std::move( *texture_source_ );
//   texture_source_.reset();
//   return moved_texture_source;
// }