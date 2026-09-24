#include "core/Character/Builder.h"

#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "core/Character/Character.h"
#include "core/Character/Stats.h"
#include "engine/IGame/Coords.h"

/* ==== @PRIVATE ==== */

namespace character {

class BuilderCleanerGuard {
 private:
  character::Builder& character_builder_to_clean_;
  void resetCharacterBuilder() noexcept {
    character_builder_to_clean_.name_ = std::nullopt;
    character_builder_to_clean_.coords_ = std::nullopt;
    character_builder_to_clean_.stats_ = std::nullopt;
    character_builder_to_clean_.is_user_ = std::nullopt;
  }

 public:
  BuilderCleanerGuard( character::Builder& character_builder_to_clean ) noexcept
      : character_builder_to_clean_( character_builder_to_clean ) {
  }
  ~BuilderCleanerGuard() noexcept {
    resetCharacterBuilder();
  }
};

}  // namespace character

[[nodiscard]] int character::Builder::generateId() noexcept {
  static int base_id = 0;
  return ++base_id;
}

void character::Builder::generateDefaultsForUnsetParams() noexcept {
  if ( !name_ ) {
    name_ = "John";
  }
  if ( !coords_ ) {
    coords_ = { 0, 0 };
  }
  if ( !stats_ ) {
    stats_ = character::Stats{};
  }
  if ( !is_user_ ) {
    is_user_ = false;
  }
}

/* ==== @PUBLIC ==== */

[[nodiscard]] character::Builder&& character::Builder::setName( std::string name ) && noexcept {
  name_ = std::move( name );
  return std::move( *this );
}

[[nodiscard]] character::Builder&& character::Builder::setCoords( CoordPair coords ) && noexcept {
  coords_ = coords;
  return std::move( *this );
}

[[nodiscard]] character::Builder&& character::Builder::setStats( character::Stats stats ) && noexcept {
  stats_ = std::move( stats );
  return std::move( *this );
}

[[nodiscard]] character::Builder&& character::Builder::setIsUser( bool is_user ) && noexcept {
  is_user_ = is_user;
  return std::move( *this );
}

Character character::Builder::build() && noexcept {
  character::BuilderCleanerGuard guard{ *this };
  int id = generateId();
  generateDefaultsForUnsetParams();

  return Character{ id, std::move( *name_ ), *coords_, std::move( *stats_ ), *is_user_ };
}

std::shared_ptr<Character> character::Builder::buildSharedPtr() && noexcept {
  character::BuilderCleanerGuard guard{ *this };
  int id = generateId();
  generateDefaultsForUnsetParams();

  return std::make_shared<Character>( id, std::move( *name_ ), *coords_, std::move( *stats_ ), *is_user_ );
}