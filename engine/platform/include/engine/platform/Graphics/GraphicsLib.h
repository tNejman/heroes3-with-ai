#pragma once

#include <string>
namespace graphics {

constexpr inline int WINDOW_WIDTH = 800;
constexpr inline int WINDOW_HEIGHT = 600;

constexpr inline int WORLD_MAP_MAX_TILES_SEEN_LEFT = 12U;
constexpr inline int WORLD_MAP_MAX_TILES_SEEN_RIGHT = 12U;
constexpr inline int WORLD_MAP_MAX_TILES_SEEN_UP = 9U;
constexpr inline int WORLD_MAP_MAX_TILES_SEEN_DOWN = 9U;

constexpr inline int TERRAIN_SPRITE_HEIGHT = 32;
constexpr inline int TERRAIN_SPRITE_WIDTH = 32;

constexpr inline int HERO_SPRITE_WIDTH_DEPRECATED = 95;
constexpr inline int HERO_SPRITE_HEIGHT_DEPRECATED = 64;

const std::string HEXAGON_SPRITE_DEFAULT_PATH = "Sprites/Battle/Auxiliary/Hexagon.png";
const std::string HEXAGON_MOVEMENT_SPRITE_PATH = "Sprites/Battle/Auxiliary/Hexagon_Movement.png";
const std::string HEXAGON_ATTACK_SPRITE_PATH = "Sprites/Battle/Auxiliary/Hexagon_Attack.png";

constexpr inline int HEXAGON_SPRITE_WIDTH = 48;
constexpr inline int HEXAGON_SPRITE_HEIGHT = 56;

constexpr inline int BATTLE_MAP_SPRITE_X_DELTA = 48;
constexpr inline int BATTLE_MAP_SPRITE_Y_DELTA = 86;

constexpr inline int BATTLE_MAP_SPRITE_INITIAL_OFFSET_X_ODD = 24;
constexpr inline int BATTLE_MAP_SPRITE_INITIAL_OFFSET_Y_ODD = 24;
constexpr inline int BATTLE_MAP_SPRITE_INITIAL_OFFSET_Y_ODD_UNIT = 64;

constexpr inline int BATTLE_MAP_SPRITE_ADJUST_EVEN_X = 24;
constexpr inline int BATTLE_MAP_SPRITE_ADJUST_EVEN_Y = 43;

constexpr double HEXAGON_SPRITE_MAX_RADIUS = HEXAGON_SPRITE_WIDTH / 2.0;

}  // namespace graphics