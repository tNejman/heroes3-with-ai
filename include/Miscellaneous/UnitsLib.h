#pragma once
// Autor: Tomasz Nejman i Tomasz Naszkowski
/* Zawartość klasy unitlib:
    - klasa pozwala na przechowywanie jednostek
    - klasa pozwala na tworzenie jednostek
    - klasa pozwala na dodawanie jednostek do armii
*/
#include <cstdint>
#include <map>
#include <memory>
#include <string>

class Faction;
class Resource;

enum class FactionAttitude { EVIL, NEUTRAL, GOOD };

enum class FactionType : int { FORGE, CONFLUX, CASTLE };

enum class ForgeUnitType : int {
  GRUNT = 0,
  CYBER_DEAD = 1,
  PYRO = 2,
  STINGER = 3,
  JUMP_SOLDIER = 4,
  TANK = 5,
  JUGGERNAUT = 6
};

enum class ConfluxUnitType : int {
  PIXIE = 0,
  AIR_ELEMENTAL = 1,
  WATER_ELEMENTAL = 2,
  FIRE_ELEMENTAL = 3,
  EARTH_ELEMENTAL = 4,
  PSYCHIC_ELEMENTAL = 5,
  FIREBIRD = 6
};

enum class CastleUnitType : int {
  PIKEMAN = 0,
  ARCHER = 1,
  GRIFFIN = 2,
  SWORDSMAN = 3,
  MONK = 4,
  CAVALIER = 5,
  ANGEL = 6
};

struct UnitData {
  std::string name_;
  uint32_t level_;
  uint32_t attack_;
  uint32_t defense_;
  uint32_t min_damage_;
  uint32_t max_damage_;
  uint32_t health_;
  uint32_t speed_;
  uint32_t counter_attack_;
  uint32_t growth_;
  uint32_t cost_;
  uint32_t fight_value_;
  std::string path_to_texture_;
};

// @Warning @deprecated
const std::map<ForgeUnitType, const std::shared_ptr<const UnitData>> UNITS_PRESET_FORGE = {
    // not actual stats, just placeholders
    { ForgeUnitType::GRUNT, std::make_shared<const UnitData>( "grunt", 1U, 10U, 5U, 10U, 20U, 20U, 10U, 10U, 10U, 500U,
                                                              999'999'999U, "/path/folder/tex1" ) },
    { ForgeUnitType::CYBER_DEAD, std::make_shared<const UnitData>( "cyber dead", 1U, 10U, 5U, 10U, 20U, 20U, 10U, 10U,
                                                                   10U, 500U, 999'999'999U, "/path/folder/tex2" ) } };

const std::map<ConfluxUnitType, const std::shared_ptr<const UnitData>> UNITS_PRESET_CONFLUX;

const std::map<CastleUnitType, const std::shared_ptr<const UnitData>> UNITS_PRESET_CASTLE = {
    { CastleUnitType::PIKEMAN, std::make_shared<const UnitData>( "pikeman", 1U, 4U, 5U, 1U, 3U, 10U, 4U, 1U, 14U, 60U,
                                                                 100U, "/path/folder/tex1" ) },
    { CastleUnitType::ARCHER, std::make_shared<const UnitData>( "archer", 2U, 6U, 3U, 2U, 3U, 10U, 4U, 1U, 9U, 100U,
                                                                115U, "/path/folder/tex2" ) },
    { CastleUnitType::GRIFFIN, std::make_shared<const UnitData>( "griffin", 3U, 8U, 8U, 3U, 6U, 25U, 6U, 2U, 7U, 200U,
                                                                 324U, "/path/folder/tex2" ) },
    { CastleUnitType::SWORDSMAN, std::make_shared<const UnitData>( "swordsman", 4U, 10U, 12U, 6U, 9U, 35U, 5U, 1U, 4U,
                                                                   300U, 445U, "/path/folder/tex2" ) },
    { CastleUnitType::MONK, std::make_shared<const UnitData>( "monk", 5U, 12U, 7U, 10U, 12U, 30U, 5U, 1U, 3U, 400U,
                                                              485U, "/path/folder/tex2" ) },
    { CastleUnitType::CAVALIER, std::make_shared<const UnitData>( "cavalier", 6U, 15U, 15U, 15U, 25U, 100U, 7U, 1U, 2U,
                                                                  1000U, 1668U, "/path/folder/tex2" ) },
    { CastleUnitType::ANGEL, std::make_shared<const UnitData>( "angel", 7U, 30U, 30U, 50U, 50U, 200U, 12U, 1U, 1U,
                                                               3000U, 3585U, "/path/folder/tex2" ) } };