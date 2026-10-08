#pragma once

#include <string>

#include "aux/Builder.hpp"
#include "core/Misc/BuilderDefaults.hpp"
#include "core/Character/Character.h"
#include "core/Character/Stats.h"
#include "engine/IGame/Coords.h"

// NOLINTBEGIN(readability-identifier-naming)

template <>
struct BuilderDefaults<Character> {
  static constexpr CoordPair coords{ 0, 0 };
  static constexpr character::Type type = character::Type::FIRE_HERO;
  static inline const std::string name{ "John" };
  static constexpr bool is_user = false;
  static constexpr character::Stats stats{};
};

template <>
struct BuilderIdGenerator<Character> {
    static inline auto generator = [next_id = 0]() mutable -> int { return next_id++; };
};

// NOLINTEND(readability-identifier-naming)