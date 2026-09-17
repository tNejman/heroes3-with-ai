#include "engine/Graphics/SpriteVisitor.h"

#include <SFML/Graphics/Sprite.hpp>
#include <optional>
#include <utility>

#include "core/Artifact/Artifact.h"
#include "core/Battle/Battle.h"
#include "core/Battle/Obstacle.hpp"
#include "core/Character/Character.h"
#include "core/Character/SecondarySkill.h"
#include "aux/Err.hpp"
#include "engine/Graphics/SpriteFactory.h"
#include "engine/Graphics/Visitor.h"
#include "core/Magic/Spell.h"
#include "core/Resource/Resource.h"
#include "core/WorldMap/OverworldObstacle.h"

void SpriteVisitor::visit( const Artifact& e ) {
  sprite_ = SpriteFactory::getSpriteFromBindingV( e.getData().type_ );
}

void SpriteVisitor::visit( const Obstacle& ) {
  err::passCondOrAbort( false, "not implemented: OBSTACLE" );
}

void SpriteVisitor::visit( const Character& e ) {
  sprite_ = SpriteFactory::getSpriteFromBindingV( e.getCharacterType(), e.getOrientation() );
}

void SpriteVisitor::visit( const SecondarySkill& ) {
  err::passCondOrAbort( false, "not implemented: SECONDARY SKILL" );
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
