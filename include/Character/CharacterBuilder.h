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

  [[nodiscard]] static int generateId() noexcept;

 public:
  [[nodiscard]] CharacterBuilder&& setName( std::string name ) && noexcept;
  [[nodiscard]] CharacterBuilder&& setCoords( CoordPair coords ) && noexcept;
  [[nodiscard]] CharacterBuilder&& setStats( CharacterStats stats ) && noexcept;
  [[nodiscard]] Character build() && noexcept;
  [[nodiscard]] std::shared_ptr<Character> buildSharedPtr() && noexcept;
};