#include "core/Character/CharacterBuilder.h"

#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "core/Character/Character.h"
#include "core/Character/CharacterStats.h"
#include "core/Misc/Coords.h"

/* ==== @PRIVATE ==== */

class CharacterBuilderCleanerGuard {
 private:
  CharacterBuilder& character_builder_to_clean_;
  void resetCharacterBuilder() noexcept {
    character_builder_to_clean_.name_ = std::nullopt;
    character_builder_to_clean_.coords_ = std::nullopt;
    character_builder_to_clean_.stats_ = std::nullopt;
    character_builder_to_clean_.is_user_ = std::nullopt;
  }

 public:
  CharacterBuilderCleanerGuard( CharacterBuilder& character_builder_to_clean ) noexcept
      : character_builder_to_clean_( character_builder_to_clean ) {
  }
  ~CharacterBuilderCleanerGuard() noexcept {
    resetCharacterBuilder();
  }
};

[[nodiscard]] int CharacterBuilder::generateId() noexcept {
  static int base_id = 0;
  return ++base_id;
}

void CharacterBuilder::generateDefaultsForUnsetParams() noexcept {
  if ( !name_ ) {
    name_ = "John";
  }
  if ( !coords_ ) {
    coords_ = { 0, 0 };
  }
  if ( !stats_ ) {
    stats_ = CharacterStats{};
  }
  if ( !is_user_ ) {
    is_user_ = false;
  }
}

/* ==== @PUBLIC ==== */

[[nodiscard]] CharacterBuilder&& CharacterBuilder::setName( std::string name ) && noexcept {
  name_ = std::move( name );
  return std::move( *this );
}

[[nodiscard]] CharacterBuilder&& CharacterBuilder::setCoords( CoordPair coords ) && noexcept {
  coords_ = coords;
  return std::move( *this );
}

[[nodiscard]] CharacterBuilder&& CharacterBuilder::setStats( CharacterStats stats ) && noexcept {
  stats_ = std::move( stats );
  return std::move( *this );
}

[[nodiscard]] CharacterBuilder&& CharacterBuilder::setIsUser( bool is_user ) && noexcept {
  is_user_ = is_user;
  return std::move( *this );
}

Character CharacterBuilder::build() && noexcept {
  CharacterBuilderCleanerGuard guard{ *this };
  int id = generateId();
  generateDefaultsForUnsetParams();

  return Character{ id, std::move( *name_ ), *coords_, std::move( *stats_ ), *is_user_ };
}

std::shared_ptr<Character> CharacterBuilder::buildSharedPtr() && noexcept {
  CharacterBuilderCleanerGuard guard{ *this };
  int id = generateId();
  generateDefaultsForUnsetParams();

  return std::make_shared<Character>( id, std::move( *name_ ), *coords_, std::move( *stats_ ), *is_user_ );
}