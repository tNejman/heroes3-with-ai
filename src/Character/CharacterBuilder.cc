#include "Character/CharacterBuilder.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include "Character/Character.h"
#include "Character/CharacterStats.h"
#include "Exceptions/Err.hpp"
#include "Miscellaneous/Coords.h"

[[nodiscard]] int CharacterBuilder::generateId() noexcept {
  static int base_id = 0;
  return ++base_id;
}

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

Character CharacterBuilder::build() && noexcept {
  // TODO maybe change default
  int id = generateId();

  if ( !name_ ) {
    name_ = "John";
  }
  if ( !coords_ ) {
    coords_ = { 0, 0 };
  }
  if ( !stats_ ) {
    stats_ = CharacterStats{};
  }
  return Character{ id, std::move( *name_ ), *coords_, std::move( *stats_ ) };
}

std::shared_ptr<Character> CharacterBuilder::buildSharedPtr() && noexcept {
  // TODO maybe change default
  int id = generateId();

  if ( !name_ ) {
    name_ = "John";
  }
  if ( !coords_ ) {
    coords_ = { 0, 0 };
  }
  if ( !stats_ ) {
    stats_ = CharacterStats{};
  }
  return std::make_shared<Character>( id, std::move( *name_ ), *coords_, std::move( *stats_ ) );
}