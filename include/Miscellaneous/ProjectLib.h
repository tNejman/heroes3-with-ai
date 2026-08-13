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

constexpr inline int WORLD_MAP_WIDTH = 100;   // 20
constexpr inline int WORLD_MAP_HEIGHT = 100;  // 20

constexpr double INF_SCORE = 1e9;

constexpr std::array<ShiftPair, 8> WORLD_MAP_DIRECTIONS = { { ShiftPair{ -1, 1 },      // UL
                                                              ShiftPair{ 0, 1 },       // U
                                                              ShiftPair{ 1, 1 },       // UR
                                                              ShiftPair{ -1, 0 },      // R
                                                              ShiftPair{ 1, 0 },       // DR
                                                              ShiftPair{ -1, -1 },     // D
                                                              ShiftPair{ 0, -1 },      // DL
                                                              ShiftPair{ 1, -1 } } };  // L

enum class CharacterMoveDirection : uint8_t { UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, NONE };

/*
====== BATTLE ======
*/

constexpr inline int MAP_WIDTH_BF = 15;
constexpr inline int MAP_HEIGHT_BF = 11;

enum BATTLE_DIRECTIONS : int { UR, R, DR, DL, L, UL };

// {0,0} in the middle, top and bottom rows are shifted right
constexpr std::array<ShiftPair, 6> EVEN_DIRECTIONS_BATTLE = { {
    { 1, 1 },   // UR
    { 1, 0 },   // R
    { 1, -1 },  // DR
    { 0, -1 },  // DL
    { -1, 0 },  // L
    { 0, 1 }    // UL
} };
/*
   EVEN_DIRECTIONS_BATTLE visual below
        {0, 1}, {1, 1},
   {-1,0},         {1, 0},
        {0,-1}, {1,-1}
*/

// {0,0} in the middle, top and bottom rows are shifted left
constexpr std::array<ShiftPair, 6> ODD_DIRECTIONS_BATTLE = { {
    { 0, 1 },    // UR
    { 1, 0 },    // R
    { 0, -1 },   // DR
    { -1, -1 },  // DL
    { -1, 0 },   // L
    { -1, 1 }    // UL
} };
/*
    ODD_DIRECTIONSS_BATTLE visual below
        {-1, 1}, { 0, 1},
    {-1, 0},        { 1, 0},
        {-1,-1}, {0, -1}
*/

constexpr inline int MELEE_UNIT_RANGE = 1;

constexpr CoordPair BATTLE_MAP_TOP_RIGHT_COORDS{ MAP_WIDTH_BF - 1, MAP_HEIGHT_BF - 1 };
constexpr CoordPair BATTLE_MAP_NOT_FOUND_COORDS{ 69'420, 69'420 };
// constexpr CoordPair BATTLE_MAP_PASS_COORDS = CoordPair( 100u, 100u );

/*
====== TERRAIN ======
*/

enum class Terrain : uint8_t {
  GRASS = 0,
  DIRT = 1,
  MOSTLY_GRASS = 2,
  ROCKS = 3,
  ROCKS_CRUSHED = 4,
  SAND = 5,
  COUNT = 6
};

const std::unordered_map<Terrain, double> TERRAIN_MOVEMENT_PENALTY = { { Terrain::GRASS, 1.0 },
                                                                       { Terrain::DIRT, 1.2 } };

/*
====== CHARACTER ======
*/

enum class CharacterType { FIRE_HERO, BLACK_HERO_WHITE_HORSE };

constexpr std::array<int, 11> EXPERIENCE_THRESHHOLDS = {
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

const std::map<int, int> SPEED_TO_MOVEMENT = { {
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

// constexpr sf::Time FRAME_DURATION = sf::seconds( 1.f / 30.f );

constexpr inline int KEY_BUFFER_DURATION = 5;

constexpr sf::Keyboard::Key W = sf::Keyboard::Key::W;
constexpr sf::Keyboard::Key S = sf::Keyboard::Key::S;
constexpr sf::Keyboard::Key A = sf::Keyboard::Key::A;
constexpr sf::Keyboard::Key D = sf::Keyboard::Key::D;
constexpr std::array<sf::Keyboard::Key, 4> MOVEMENT_KEYS = { W, S, A, D };

const std::map<sf::Keyboard::Key, std::vector<sf::Keyboard::Key>> VALID_DIAGONAL_MOVE_COMP = {
    { W, { A, D } }, { S, { A, D } }, { A, { W, S } }, { D, { W, S } } };

constexpr inline int WORLD_MAP_MAX_TILES_SEEN_LEFT = 12U;
constexpr inline int WORLD_MAP_MAX_TILES_SEEN_RIGHT = 12U;
constexpr inline int WORLD_MAP_MAX_TILES_SEEN_UP = 9U;
constexpr inline int WORLD_MAP_MAX_TILES_SEEN_DOWN = 9U;

constexpr inline int WINDOW_WIDTH = 800;
constexpr inline int WINDOW_HEIGHT = 600;

constexpr inline int TERRAIN_SPRITE_HEIGHT = 32;
constexpr inline int TERRAIN_SPRITE_WIDTH = 32;

constexpr inline int HERO_SPRITE_WIDTH = 95;
constexpr inline int HERO_SPRITE_HEIGHT = 64;

const std::string HEXAGON_SPRITE_DEFAULT_PATH = "Sprites/Battle/Auxiliary/Hexagon.png";
const std::string HEXAGON_MOVEMENT_SPRITE_PATH = "Sprites/Battle/Auxiliary/Hexagon_Movement.png";
const std::string HEXAGON_ATTACK_SPRITE_PATH = "Sprites/Battle/Auxiliary/Hexagon_Attack.png";

constexpr inline int HEXAGON_SPRITE_WIDTH = 48;
constexpr inline int HEXAGON_SPRITE_HEIGHT = 56;

constexpr inline int BATTLE_MAP_SPRITE_X_DELTA = 48;
constexpr inline int BATTLE_MAP_SPRITE_Y_DELTA = 86;

constexpr inline int BATTLE_MAP_SPRITE_INITAL_OFFSET_X_ODD = 24;
constexpr inline int BATTLE_MAP_SPRITE_INITAL_OFFSET_Y_ODD = 24;
constexpr inline int BATTLE_MAP_SPRITE_INITAL_OFFSET_Y_ODD_UNIT = 64;

constexpr inline int BATTLE_MAP_SPRITE_ADJUST_EVEN_X = 24;
constexpr inline int BATTLE_MAP_SPRITE_ADJUST_EVEN_Y = 43;

constexpr double HEXAGON_SPRITE_MAX_RADIUS = HEXAGON_SPRITE_WIDTH / 2.0;

const std::string WORLD_MAP_INPUT_PATH = "in/world_map_in_2.txt";

const std::string WINDOW_NAME = "Heroes3App";

/*
====== MISC ======
*/

constexpr std::size_t AMOUNT_OF_RESOURCES = 7;

constexpr inline int FACTION_FORGE_ID_MARKER = 0;
constexpr inline int FACTION_CONFLUX_ID_MARKER = 1;
constexpr inline int FACTION_CASTLE_ID_MARKER = 2;

/*
====== MINIMAX ======
*/

constexpr inline int MINIMAX_MAX_DEPTH = 5U;

/*
====== SAVING AND LOADING ======
*/
const std::string CHARACTER_SAVE_START_MARKER = "CHARACTER";