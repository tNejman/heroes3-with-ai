#include "Artifact/Artifact.h"

#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <cassert>
#include <memory>

#include "Artifact/ArtifactLib.h"
#include "Graphics/Visitor.h"

Artifact::Artifact( const ArtifactData& data ) : data_( data ) {
}

[[nodiscard]] sf::Texture& Artifact::accept( Visitor& vis ) const {
  return vis.visit( *this );
}

[[nodiscard]] Artifact Artifact::create( const ArtifactType type ) noexcept {
  const auto* it =
      std::ranges::find_if( artifact_lib::ARTIFACTS_PRESET, [type]( const auto& data ) { return type == data.type_; } );
  assert( it != artifact_lib::ARTIFACTS_PRESET.end() );
  return *it;
}

[[nodiscard]] const ArtifactData& Artifact::getData() const noexcept {
  return data_.get();
}

[[nodiscard]] Artifact Artifact::copy() const noexcept {
  return create( data_.get().type_ );
}

bool Artifact::operator==( const Artifact& other ) const noexcept {
  return this == &other || data_.get() == other.getData();
}