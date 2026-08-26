#include "Graphics/SpriteVisitor.h"

#include <SFML/Graphics/Sprite.hpp>
#include <optional>
#include <utility>

#include "Artifact/Artifact.h"
#include "Battle/Battle.h"
#include "Battle/Obstacle.hpp"
#include "Character/Character.h"
#include "Character/SecondarySkill.h"
#include "Exceptions/Err.hpp"
#include "Graphics/SpriteFactory.h"
#include "Graphics/Visitor.h"
#include "Magic/Spell.h"
#include "Resource/Resource.h"
#include "WorldMap/OverworldObstacle.h"

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
