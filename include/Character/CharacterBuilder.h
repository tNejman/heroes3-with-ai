#pragma once

#include <memory>
#include <optional>
#include <string>

#include "Character/Character.h"
#include "Character/CharacterStats.h"
#include "Miscellaneous/Coords.h"
class CharacterBuilder {
 private:
  std::optional<std::string> name_;
  std::optional<CoordPair> coords_;
  std::optional<CharacterStats> stats_;

 public:
  CharacterBuilder&& setName( std::string name ) && noexcept;
  CharacterBuilder&& setCoords( CoordPair coords ) && noexcept;
  CharacterBuilder&& setStats( CharacterStats stats ) && noexcept;
  Character build() && noexcept;
  std::shared_ptr<Character> buildSharedPtr() && noexcept;
};