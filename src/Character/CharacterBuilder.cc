#include "Character/CharacterBuilder.h"

#include <stdexcept>
#include <string>
#include <utility>

#include "Character/Character.h"
#include "Character/CharacterStats.h"
#include "Exceptions/Err.hpp"
#include "Miscellaneous/Coords.h"

CharacterBuilder&& CharacterBuilder::setName( std::string name ) && noexcept {
  name_ = std::move( name );
  return std::move( *this );
}

CharacterBuilder&& CharacterBuilder::setCoords( CoordPair coords ) && noexcept {
  coords_ = coords;
  return std::move( *this );
}

CharacterBuilder&& CharacterBuilder::setStats( CharacterStats stats ) && noexcept {
  stats_ = std::move( stats );
  return std::move( *this );
}

Character CharacterBuilder::build() {
  // TODO maybe change default
  if ( !name_ ) {
    name_ = "John";
  }
  if ( !coords_ ) {
    coords_ = { 0, 0 };
  }
  if ( !stats_ ) {
    err::raise<std::runtime_error>( "no stats" );
  }
  return Character{ std::move( *name_ ), *coords_, std::move( *stats_ ) };
}