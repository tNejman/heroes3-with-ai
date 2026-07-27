
#pragma once

#include <map>
#include <string>

#include "Miscellaneous/ProjectLib.h"

const std::map<CharacterType, std::string> CHARACTER_TYPE_TO_STRING = {
    { CharacterType::FIRE_HERO, "fire_hero" }, { CharacterType::BLACK_HERO_WHITE_HORSE, "black_her_white_horse" } };

const std::map<CharacterMoveDirection, std::string> CHARACTER_ORIENTATION_TO_STRING = {
    { CharacterMoveDirection::UP, "_up" },       { CharacterMoveDirection::UP_RIGHT, "_up_right" },
    { CharacterMoveDirection::RIGHT, "_right" }, { CharacterMoveDirection::DOWN_RIGHT, "_down_right" },
    { CharacterMoveDirection::DOWN, "_down" },   { CharacterMoveDirection::DOWN_LEFT, "_down_left" },
    { CharacterMoveDirection::LEFT, "_left" },   { CharacterMoveDirection::UP_LEFT, "_up_left" } };