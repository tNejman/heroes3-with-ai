#pragma once

#include <variant>

#include "Miscellaneous/Coords.h"

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

using WorldMapGameCommand = std::variant<MoveMapObject, EraseTile, PlaceCharacter>;

/* === TOWN === */

using TownGameCommand = std::variant<std::monostate>;

/* === BATTLE === */

using BattleGameCommand = std::variant<std::monostate>;

/* === GENERAL WRAPPER === */

using GameCommand = std::variant<WorldMapGameCommand, TownGameCommand, BattleGameCommand>;