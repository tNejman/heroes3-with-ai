#pragma once
// Autor: Tomasz Nejman
// zawartość: zawiera stałe używane w grze

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "Miscellaneous/Coords.h"

/*
====== WORLD MAP ======
*/

constexpr uint32_t WORLD_MAP_WIDTH = 100;   // 20
constexpr uint32_t WORLD_MAP_HEIGHT = 100;  // 20

constexpr double INF_SCORE = 1e9;

constexpr std::array<ShiftPair, 8> WORLD_MAP_DIRECTIONS = { { { .dx_ = -1, .dy_ = 1 },      // UL
                                                              { .dx_ = 0, .dy_ = 1 },       // U
                                                              { .dx_ = 1, .dy_ = 1 },       // UR
                                                              { .dx_ = -1, .dy_ = 0 },      // R
                                                              { .dx_ = 1, .dy_ = 0 },       // DR
                                                              { .dx_ = -1, .dy_ = -1 },     // D
                                                              { .dx_ = 0, .dy_ = -1 },      // DL
                                                              { .dx_ = 1, .dy_ = -1 } } };  // L

enum class CharacterMoveDirection { UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, NONE };

/*
====== BATTLE ======
*/

constexpr uint32_t MAP_WIDTH_BF = 15;
constexpr uint32_t MAP_HEIGHT_BF = 11;

enum BATTLE_DIRECTIONS : int { UR, R, DR, DL, L, UL };

// {0,0} in the middle, top and bottom rows are shifted right
constexpr std::array<ShiftPair, 6> EVEN_DIRECTIONS_BATTLE = { {
    { .dx_ = 1, .dy_ = 1 },   // UR
    { .dx_ = 1, .dy_ = 0 },   // R
    { .dx_ = 1, .dy_ = -1 },  // DR
    { .dx_ = 0, .dy_ = -1 },  // DL
    { .dx_ = -1, .dy_ = 0 },  // L
    { .dx_ = 0, .dy_ = 1 }    // UL
} };
/*
   EVEN_DIRECTIONS_BATTLE visual below
        {0, 1}, {1, 1},
   {-1,0},         {1, 0},
        {0,-1}, {1,-1}
*/

// {0,0} in the middle, top and bottom rows are shifted left
constexpr std::array<ShiftPair, 6> ODD_DIRECTIONS_BATTLE = { {
    { .dx_ = 0, .dy_ = 1 },    // UR
    { .dx_ = 1, .dy_ = 0 },    // R
    { .dx_ = 0, .dy_ = -1 },   // DR
    { .dx_ = -1, .dy_ = -1 },  // DL
    { .dx_ = -1, .dy_ = 0 },   // L
    { .dx_ = -1, .dy_ = 1 }    // UL
} };
/*
    ODD_DIRECTIONSS_BATTLE visual below
        {-1, 1}, { 0, 1},
    {-1, 0},        { 1, 0},
        {-1,-1}, {0, -1}
*/

constexpr uint32_t MELEE_UNIT_RANGE = 1;

constexpr CoordPair BATTLE_MAP_TOP_RIGHT_COORDS{ .x_ = MAP_WIDTH_BF - 1, .y_ = MAP_HEIGHT_BF - 1 };
constexpr CoordPair BATTLE_MAP_NOT_FOUND_COORDS{ .x_ = 69'420U, .y_ = 69'420U };
// constexpr CoordPair BATTLE_MAP_PASS_COORDS = CoordPair( 100u, 100u );

/*
====== TERRAIN ======
*/

enum class Terrain { GRASS = 0, DIRT = 1, MOSTLY_GRASS = 2, ROCKS = 3, ROCKS_CRUSHED = 4, SAND = 5 };

const std::unordered_map<Terrain, double> TERRAIN_MOVEMENT_PENALTY = { { Terrain::GRASS, 1.0 },
                                                                       { Terrain::DIRT, 1.2 } };

/*
====== CHARACTER ======
*/

constexpr uint32_t SECONDARY_SKILLS_SLOTS_COUNT = 8;
constexpr uint32_t EQUIPMENT_SLOTS_COUNT = 14;
constexpr uint32_t MAX_BACKPACK_SIZE = 64;
constexpr uint32_t MAX_PARTY_SIZE = 7;

enum class CharacterType { FIRE_HERO, BLACK_HERO_WHITE_HORSE };

enum class EquipmentSlots {
  HELMET = 0,
  CAPE = 1,
  NECKLACE = 2,
  WEAPON = 3,
  SHIELD = 4,
  TORSO = 5,
  RING = 6,
  RING_1 = 7,
  RING_2 = 8,
  FEET = 9,
  MISC = 10,
  MISC_1 = 10,
  MISC_2 = 11,
  MISC_3 = 12,
  MISC_4 = 13,
  MISC_5 = 14
};

constexpr std::array<uint32_t, 11> EXPERIENCE_THRESHHOLDS = {
    0,      // 0
    0,      // 1
    1000,   // 2
    2000,   // 3
    3200,   // 4
    4600,   // 5
    6200,   // 6
    8000,   // 7
    10000,  // 8
    12200,  // 9
    14700   // 10 and above
};

const std::map<uint32_t, uint32_t> SPEED_TO_MOVEMENT = { {
    { 3, 1500 },
    { 4, 1560 },
    { 5, 1630 },
    { 6, 1700 },
    { 7, 1760 },
    { 8, 1830 },
    { 9, 1900 },
    { 10, 1960 },
    { 11, 2000 }  // accounts for 11 or more
} };

/*
===== RENDERING =====
*/

using FrameCount = uint32_t;

// constexpr sf::Time FRAME_DURATION = sf::seconds( 1.f / 30.f );

constexpr FrameCount KEY_BUFFER_DURATION = 5;

constexpr sf::Keyboard::Key W = sf::Keyboard::Key::W;
constexpr sf::Keyboard::Key S = sf::Keyboard::Key::S;
constexpr sf::Keyboard::Key A = sf::Keyboard::Key::A;
constexpr sf::Keyboard::Key D = sf::Keyboard::Key::D;
constexpr std::array<sf::Keyboard::Key, 4> MOVEMENT_KEYS = { W, S, A, D };

const std::map<sf::Keyboard::Key, std::vector<sf::Keyboard::Key>> VALID_DIAGONAL_MOVE_COMP = {
    { W, { A, D } }, { S, { A, D } }, { A, { W, S } }, { D, { W, S } } };

constexpr uint32_t WORLD_MAP_MAX_TILES_SEEN_LEFT = 12U;
constexpr uint32_t WORLD_MAP_MAX_TILES_SEEN_RIGHT = 12U;
constexpr uint32_t WORLD_MAP_MAX_TILES_SEEN_UP = 9U;
constexpr uint32_t WORLD_MAP_MAX_TILES_SEEN_DOWN = 9U;

constexpr uint32_t WINDOW_WIDTH = 800;
constexpr uint32_t WINDOW_HEIGHT = 600;

constexpr uint32_t TERRAIN_SPRITE_HEIGHT = 32;
constexpr uint32_t TERRAIN_SPRITE_WIDTH = 32;

constexpr uint32_t HERO_SPRITE_WIDTH = 95;
constexpr uint32_t HERO_SPRITE_HEIGHT = 64;

const std::string HEXAGON_SPRITE_DEFAULT_PATH = "Sprites/Battle/Auxiliary/Hexagon.png";
const std::string HEXAGON_MOVEMENT_SPRITE_PATH = "Sprites/Battle/Auxiliary/Hexagon_Movement.png";
const std::string HEXAGON_ATTACK_SPRITE_PATH = "Sprites/Battle/Auxiliary/Hexagon_Attack.png";

constexpr uint32_t HEXAGON_SPRITE_WIDTH = 48;
constexpr uint32_t HEXAGON_SPRITE_HEIGHT = 56;

constexpr uint32_t BATTLE_MAP_SPRITE_X_DELTA = 48;
constexpr uint32_t BATTLE_MAP_SPRITE_Y_DELTA = 86;

constexpr uint32_t BATTLE_MAP_SPRITE_INITAL_OFFSET_X_ODD = 24;
constexpr uint32_t BATTLE_MAP_SPRITE_INITAL_OFFSET_Y_ODD = 24;
constexpr uint32_t BATTLE_MAP_SPRITE_INITAL_OFFSET_Y_ODD_UNIT = 64;

constexpr uint32_t BATTLE_MAP_SPRITE_ADJUST_EVEN_X = 24;
constexpr uint32_t BATTLE_MAP_SPRITE_ADJUST_EVEN_Y = 43;

constexpr double HEXAGON_SPRITE_MAX_RADIUS = HEXAGON_SPRITE_WIDTH / 2.0;

const std::string WORLD_MAP_INPUT_PATH = "in/world_map_in_2.txt";

const std::string WINDOW_NAME = "Heroes3App";

/*
====== MISC ======
*/

constexpr std::size_t AMOUNT_OF_RESOURCES = 7;

enum class GameState { OVERWORLD, BATTLE, MENU };

/*
====== MINIMAX ======
*/

constexpr uint32_t MINIMAX_MAX_DEPTH = 5U;