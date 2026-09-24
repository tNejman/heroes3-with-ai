#include "core/Artifact/Artifact.h"

#include <cassert>
#include <cstddef>

#include "core/Artifact/ArtifactLib.h"
#include "engine/Graphics/Visitor.h"

Artifact::Artifact( const artifact::Data& data ) : data_( data ) {
}

void Artifact::accept( Visitor& vis ) const {
  vis.visit( *this );
}

[[nodiscard]] Artifact Artifact::create( const artifact::Type type ) noexcept {
  return Artifact{ artifact::PRESET[static_cast<size_t>( type )] };
}

[[nodiscard]] const artifact::Data& Artifact::getData() const noexcept {
  return data_.get();
}

[[nodiscard]] Artifact Artifact::copy() const noexcept {
  return create( data_.get().type_ );
}

bool Artifact::operator==( const Artifact& other ) const noexcept {
  return this == &other || data_.get() == other.getData();
}