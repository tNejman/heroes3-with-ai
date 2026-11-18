#include "core/Artifact/Artifact.h"

#include <cassert>
#include <cstddef>

#include "engine/model/IGraphics/Visitor.h"

#include "core/Artifact/ArtifactLib.h"

Artifact::Artifact( const artifact::Data& data ) noexcept : data_( data ) {
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