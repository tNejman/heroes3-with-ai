#pragma once

#include <memory>
#include <optional>
#include <string>

#include "core/Character/Character.h"
#include "core/Character/Stats.h"
#include "engine/IGame/Coords.h"

namespace character {

class Builder {
 private:
  friend class BuilderCleanerGuard;

  std::optional<std::string> name_;
  std::optional<CoordPair> coords_;
  std::optional<character::Stats> stats_;
  std::optional<bool> is_user_;

  [[nodiscard]] static int generateId() noexcept;

  void generateDefaultsForUnsetParams() noexcept;

 public:
  [[nodiscard]] Builder&& setName( std::string name ) && noexcept;
  [[nodiscard]] Builder&& setCoords( CoordPair coords ) && noexcept;
  [[nodiscard]] Builder&& setStats( character::Stats stats ) && noexcept;
  [[nodiscard]] Builder&& setIsUser( bool is_user ) && noexcept;
  [[nodiscard]] Character build() && noexcept;
  [[nodiscard]] std::shared_ptr<Character> buildSharedPtr() && noexcept;
};

}  // namespace character