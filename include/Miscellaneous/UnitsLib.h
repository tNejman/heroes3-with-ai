#pragma once
// Autor: Tomasz Nejman i Tomasz Naszkowski
/* Zawartość klasy unitlib:
    - klasa pozwala na przechowywanie jednostek
    - klasa pozwala na tworzenie jednostek
    - klasa pozwala na dodawanie jednostek do armii
*/
#include <stdint.h>

#include <array>
#include <map>
#include <memory>
#include <string>

class Faction;
class Resource;

enum class FactionAttitude { EVIL,
                             NEUTRAL,
                             GOOD };

enum class FactionType : int {
  FORGE,
  CONFLUX,
  CASTLE
};

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

class UnitData {
 public:
  const std::string name_;
  const uint32_t level_;
  const uint32_t attack_;
  const uint32_t defense_;
  const uint32_t min_damage_;
  const uint32_t max_damage_;
  const uint32_t health_;
  const uint32_t speed_;
  const uint32_t counter_attack_;
  const uint32_t growth_;
  const uint32_t cost_;
  const uint32_t fight_value_;
  const std::string path_to_texture_;

  UnitData(
      const std::string& name,
      const uint32_t level,
      const uint32_t attack,
      const uint32_t defense,
      const uint32_t min_damage,
      const uint32_t max_damage,
      const uint32_t health,
      const uint32_t speed,
      const uint32_t counter_attack,
      const uint32_t growth,
      const uint32_t cost,
      const uint32_t fight_value,
      const std::string& path_to_texture ) : name_( name ),
                                             level_( level ),
                                             attack_( attack ),
                                             defense_( defense ),
                                             min_damage_( min_damage ),
                                             max_damage_( max_damage ),
                                             health_( health ),
                                             speed_( speed ),
                                             counter_attack_( counter_attack ),
                                             growth_( growth ),
                                             cost_( cost ),
                                             fight_value_( fight_value ),
                                             path_to_texture_( path_to_texture ) {};
};

// @Warning @deprecated
const std::map<ForgeUnitType, const std::shared_ptr<const UnitData>> UNITS_PRESET_FORGE = {
    // not actual stats, just placeholders
    { ForgeUnitType::GRUNT,
      std::make_shared<const UnitData>( "grunt", 1u, 10u, 5u, 10u, 20u, 20u, 10u, 10u, 10u, 500u, 999'999'999u, "/path/folder/tex1" ) },
    { ForgeUnitType::CYBER_DEAD,
      std::make_shared<const UnitData>( "cyber dead", 1u, 10u, 5u, 10u, 20u, 20u, 10u, 10u, 10u, 500u, 999'999'999u, "/path/folder/tex2" ) } };

const std::map<ConfluxUnitType, const std::shared_ptr<const UnitData>> UNITS_PRESET_CONFLUX;

const std::map<CastleUnitType, const std::shared_ptr<const UnitData>> UNITS_PRESET_CASTLE = {
    { CastleUnitType::PIKEMAN,
      std::make_shared<const UnitData>( "pikeman", 1u, 4u, 5u, 1u, 3u, 10u, 4u, 1u, 14u, 60u, 100u, "/path/folder/tex1" ) },
    { CastleUnitType::ARCHER,
      std::make_shared<const UnitData>( "archer", 2u, 6u, 3u, 2u, 3u, 10u, 4u, 1u, 9u, 100u, 115u, "/path/folder/tex2" ) },
    { CastleUnitType::GRIFFIN,
      std::make_shared<const UnitData>( "griffin", 3u, 8u, 8u, 3u, 6u, 25u, 6u, 2u, 7u, 200u, 324u, "/path/folder/tex2" ) },
    { CastleUnitType::SWORDSMAN,
      std::make_shared<const UnitData>( "swordsman", 4u, 10u, 12u, 6u, 9u, 35u, 5u, 1u, 4u, 300u, 445u, "/path/folder/tex2" ) },
    { CastleUnitType::MONK,
      std::make_shared<const UnitData>( "monk", 5u, 12u, 7u, 10u, 12u, 30u, 5u, 1u, 3u, 400u, 485u, "/path/folder/tex2" ) },
    { CastleUnitType::CAVALIER,
      std::make_shared<const UnitData>( "cavalier", 6u, 15u, 15u, 15u, 25u, 100u, 7u, 1u, 2u, 1000u, 1668u, "/path/folder/tex2" ) },
    { CastleUnitType::ANGEL,
      std::make_shared<const UnitData>( "angel", 7u, 30u, 30u, 50u, 50u, 200u, 12u, 1u, 1u, 3000u, 3585u, "/path/folder/tex2" ) } };