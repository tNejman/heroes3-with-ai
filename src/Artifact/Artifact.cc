#include "Artifact/Artifact.h"

#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "Exceptions/InvalidArtifactTypeException.hpp"
#include "MapObject/MapObject.h"
#include "Miscellaneous/ArtifactLib.h"
#include "Miscellaneous/ProjectLib.h"

Artifact::Artifact( std::shared_ptr<const ArtifactData> data )
    : MapObject( { 0U, 0U } ), artifact_data_( std::move( data ) ) {
}

std::unique_ptr<Artifact> Artifact::create( const ArtifactType type ) {
  auto it = std::find_if( ARTIFACTS_PRESET.begin(), ARTIFACTS_PRESET.end(),
                          [type]( const std::shared_ptr<const ArtifactData>& data ) { return data->type_ == type; } );

  if ( it == ARTIFACTS_PRESET.end() ) {
    throw InvalidArtifactTypeException( "Artifact type not found: " + std::to_string( static_cast<int>( type ) ) );
  } else {
    return std::make_unique<Artifact>( *it );
  }
}

sf::Texture& Artifact::accept( Visitor& v ) const {
  return v.visit( *this );
}

ArtifactType Artifact::getType() const {
  return this->artifact_data_->type_;
}

EquipmentSlots Artifact::getSlot() const {
  return this->artifact_data_->slot_;
}

const std::string& Artifact::getName() const {
  return this->artifact_data_->name_;
}

int Artifact::getAttack() const {
  return this->artifact_data_->attack_;
}

int Artifact::getDefense() const {
  return this->artifact_data_->defense_;
}

int Artifact::getPower() const {
  return this->artifact_data_->power_;
}

int Artifact::getKnowledge() const {
  return this->artifact_data_->knowledge_;
}

int Artifact::getSpeed() const {
  return this->artifact_data_->speed_;
}

size_t Artifact::getCost() const {
  return this->artifact_data_->cost_;
}

std::unique_ptr<Artifact> Artifact::copy() const {
  return std::make_unique<Artifact>( this->artifact_data_ );
}