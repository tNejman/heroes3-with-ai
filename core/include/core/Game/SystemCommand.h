#pragma once

#include <variant>

#include "engine/IGame/Coords.h"

/* === WORLD MAP === */

struct MoveMapObject {
  CoordPair from_;
  CoordPair to_;
};

struct EraseTile {
  CoordPair desitnation_;
};

struct PlaceCharacter {
  int character_id_;
  CoordPair destination_;
};

using WorldMapSystemCommand = std::variant<MoveMapObject, EraseTile, PlaceCharacter>;

/* === TOWN === */

struct Placeholder {};  // TODO remove

using TownSystemCommand = std::variant<Placeholder, std::monostate>;

/* === BATTLE === */

using BattleSystemCommand = std::variant<std::monostate>;

/* === GENERAL WRAPPER === */

using SystemCommand = std::variant<WorldMapSystemCommand, TownSystemCommand, BattleSystemCommand>;