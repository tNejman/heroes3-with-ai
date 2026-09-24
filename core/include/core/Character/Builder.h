#pragma once

#include <memory>
#include <optional>
#include <string>

#include "aux/IBuilder.hpp"
#include "core/Character/Character.h"
#include "core/Character/Stats.h"
#include "core/Misc/ProjectLib.h"
#include "engine/IGame/Coords.h"

// namespace character {

// class Builder {
//  private:
//   friend class BuilderCleanerGuard;

//   std::optional<CoordPair> coords_;
//   std::optional<character::Type> type_;
//   std::optional<std::string> name_;
//   std::optional<character::Stats> stats_;
//   std::optional<bool> is_user_;

//   [[nodiscard]] static int generateId() noexcept;

//   void generateDefaultsForUnsetParams() noexcept;

//  public:
//   [[nodiscard]] Builder&& setCoords( CoordPair coords ) && noexcept;
//   [[nodiscard]] Builder&& setCharacterType( character::Type type ) && noexcept;
//   [[nodiscard]] Builder&& setName( std::string name ) && noexcept;
//   [[nodiscard]] Builder&& setIsUser( bool is_user ) && noexcept;
//   [[nodiscard]] Builder&& setStats( character::Stats stats ) && noexcept;

//   [[nodiscard]] Character build() && noexcept;
//   [[nodiscard]] std::shared_ptr<Character> buildSharedPtr() && noexcept;
// };

// }  // namespace character

namespace character {

using B_CoordPair = BMember<CoordPair, CoordPair{ 0, 0 }>;
using B_CharacterType = BMember<character::Type, character::Type::FIRE_HERO>;
using B_Name = BMember<std::string, FixedString{ "John" }>;
using B_IsUser = BMember<bool, false>;
using B_Stats = BMember<character::Stats, character::Stats{}>;

struct BType {
  using
};

using Builder = Builder<>;

}  // namespace character