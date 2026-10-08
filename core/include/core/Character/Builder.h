#pragma once

#include <optional>
#include <string>

#include "aux/IBuilder.hpp"
#include "core/Character/Character.h"
#include "core/Character/Stats.h"
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

// constexpr inline CoordPair DEFAULT_COORDS{ 0, 0 };
// constexpr inline character::Type DEFAULT_TYPE{ character::Type::FIRE_HERO };
// constexpr inline FixedString DEFAULT_NAME{ "John" };
// constexpr inline bool DEFAULT_IS_USER{ false };
// constexpr inline character::Stats DEFAULT_STATS{};

// using B_CoordPair = BMember<CoordPair, character::DEFAULT_COORDS>;
// using B_CharacterType = BMember<character::Type, character::DEFAULT_TYPE>;
// using B_Name = BMember<std::string, character::DEFAULT_NAME>;
// using B_IsUser = BMember<bool, character::DEFAULT_IS_USER>;
// using B_Stats = BMember<character::Stats, character::DEFAULT_STATS>;

// using CBuilder = Builder<Character, B_CoordPair, B_CharacterType, B_Name, B_IsUser, B_Stats>;

class Builder : public IBuilder<Character, character::Builder> {
 private:
  std::optional<CoordPair> coords_;
  std::optional<character::Type> type_;
  std::optional<std::string> name_;
  std::optional<bool> is_user_;
  std::optional<character::Stats> stats_;

 protected:
  void generateDefaultsForUnsetParams() noexcept override;
  int generateId() noexcept override;

 public:
  constexpr Builder() noexcept = default;

  [[nodiscard]] Builder&& setCoords( CoordPair coords ) && noexcept;
  [[nodiscard]] Builder&& setCharacterType( character::Type type ) && noexcept;
  [[nodiscard]] Builder&& setName( std::string name ) && noexcept;
  [[nodiscard]] Builder&& setIsUser( bool is_user ) && noexcept;
  [[nodiscard]] Builder&& setStats( character::Stats stats ) && noexcept;
};

}  // namespace character