#pragma once

#include <memory>
#include <optional>
#include <string>

#include "core/Character/Character.h"
#include "core/Character/CharacterStats.h"
#include "engine/IGame/Coords.h"

class CharacterBuilder {
 private:
  friend class CharacterBuilderCleanerGuard;

  std::optional<std::string> name_;
  std::optional<CoordPair> coords_;
  std::optional<CharacterStats> stats_;
  std::optional<bool> is_user_;

  [[nodiscard]] static int generateId() noexcept;

  void generateDefaultsForUnsetParams() noexcept;

 public:
  [[nodiscard]] CharacterBuilder&& setName( std::string name ) && noexcept;
  [[nodiscard]] CharacterBuilder&& setCoords( CoordPair coords ) && noexcept;
  [[nodiscard]] CharacterBuilder&& setStats( CharacterStats stats ) && noexcept;
  [[nodiscard]] CharacterBuilder&& setIsUser( bool is_user ) && noexcept;
  [[nodiscard]] Character build() && noexcept;
  [[nodiscard]] std::shared_ptr<Character> buildSharedPtr() && noexcept;
};