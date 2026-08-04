#pragma once
// Autor: Tomasz Nejman i Tomasz Naszkowski
/* Zawartość klasy unitlib:
    - klasa pozwala na przechowywanie jednostek
    - klasa pozwala na tworzenie jednostek
    - klasa pozwala na dodawanie jednostek do armii
*/
#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <variant>

#include "Exceptions/Err.hpp"
#include "Miscellaneous/DisableCopyMoveStructHelper.hpp"

enum class FactionAttitude : uint8_t { EVIL, NEUTRAL, GOOD };

enum class FactionType : uint8_t { FORGE, CONFLUX, CASTLE };

enum class ForgeUnitType : uint8_t {
  GRUNT = 0,
  CYBER_DEAD = 1,
  PYRO = 2,
  STINGER = 3,
  JUMP_SOLDIER = 4,
  TANK = 5,
  JUGGERNAUT = 6,
  COUNT = 7
};

enum class ConfluxUnitType : uint8_t {
  PIXIE = 0,
  AIR_ELEMENTAL = 1,
  WATER_ELEMENTAL = 2,
  FIRE_ELEMENTAL = 3,
  EARTH_ELEMENTAL = 4,
  PSYCHIC_ELEMENTAL = 5,
  FIREBIRD = 6,
  COUNT = 7,
};

enum class CastleUnitType : uint8_t {
  PIKEMAN = 0,
  ARCHER = 1,
  GRIFFIN = 2,
  SWORDSMAN = 3,
  MONK = 4,
  CAVALIER = 5,
  ANGEL = 6,
  COUNT = 7,
};

enum class WarMachineType : uint8_t { BALLISTA = 0, AMMO_CART = 1, FIRST_AID_TENT = 2, CATAPULT = 3, COUNT = 4 };

// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
struct UnitData {
  const std::string name_;
  const std::variant<ForgeUnitType, ConfluxUnitType, CastleUnitType, WarMachineType> type_;
  const int level_;
  const int attack_;
  const int defense_;
  const int min_damage_;
  const int max_damage_;
  const int health_;
  const int speed_;
  const int counter_attack_;
  const int growth_;
  const int cost_;
  const int fight_value_;
  const bool is_range_;
  const std::string path_to_texture_;
  [[no_unique_address]] DisableCopyMove _no_copy_move_{};
};
// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)

const inline std::array WAR_MACHINES_PRESET = { UnitData{ .name_ = "ballista",
                                                          .type_ = WarMachineType::BALLISTA,
                                                          .level_ = 1U,
                                                          .attack_ = 0U,
                                                          .defense_ = 0U,
                                                          .min_damage_ = 0U,
                                                          .max_damage_ = 0U,
                                                          .health_ = 0U,
                                                          .speed_ = 0U,
                                                          .counter_attack_ = 0U,
                                                          .growth_ = 0U,
                                                          .cost_ = 0U,
                                                          .fight_value_ = 100U,
                                                          .is_range_ = true,
                                                          .path_to_texture_ = "/path/folder/tex1" },
                                                UnitData{ .name_ = "ammo cart",
                                                          .type_ = WarMachineType::AMMO_CART,
                                                          .level_ = 1U,
                                                          .attack_ = 0U,
                                                          .defense_ = 0U,
                                                          .min_damage_ = 0U,
                                                          .max_damage_ = 0U,
                                                          .health_ = 0U,
                                                          .speed_ = 0U,
                                                          .counter_attack_ = 0U,
                                                          .growth_ = 0U,
                                                          .cost_ = 0U,
                                                          .fight_value_ = 100U,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "first aid tent",
                                                          .type_ = WarMachineType::FIRST_AID_TENT,
                                                          .level_ = 1U,
                                                          .attack_ = 0U,
                                                          .defense_ = 0U,
                                                          .min_damage_ = 0U,
                                                          .max_damage_ = 0U,
                                                          .health_ = 0U,
                                                          .speed_ = 0U,
                                                          .counter_attack_ = 0U,
                                                          .growth_ = 0U,
                                                          .cost_ = 0U,
                                                          .fight_value_ = 100U,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex3" },
                                                UnitData{ .name_ = "catapult",
                                                          .type_ = WarMachineType::CATAPULT,
                                                          .level_ = 1U,
                                                          .attack_ = 0U,
                                                          .defense_ = 0U,
                                                          .min_damage_ = 0U,
                                                          .max_damage_ = 0U,
                                                          .health_ = 0U,
                                                          .speed_ = 0U,
                                                          .counter_attack_ = 0U,
                                                          .growth_ = 0U,
                                                          .cost_ = 0U,
                                                          .fight_value_ = 100U,
                                                          .is_range_ = true,
                                                          .path_to_texture_ = "/path/folder/tex4" } };

// @Warning @deprecated
const inline std::array UNITS_PRESET_FORGE = { UnitData{ .name_ = "grunt",
                                                         .type_ = ForgeUnitType::GRUNT,
                                                         .level_ = 1U,
                                                         .attack_ = 0U,
                                                         .defense_ = 0U,
                                                         .min_damage_ = 0U,
                                                         .max_damage_ = 0U,
                                                         .health_ = 0U,
                                                         .speed_ = 0U,
                                                         .counter_attack_ = 0U,
                                                         .growth_ = 0U,
                                                         .cost_ = 0U,
                                                         .fight_value_ = 100U,
                                                         .is_range_ = false,
                                                         .path_to_texture_ = "/path/folder/tex1" } };  // TODO

const inline std::array UNITS_PRESET_CONFLUX = { UnitData{ .name_ = "air elemental",
                                                           .type_ = ConfluxUnitType::AIR_ELEMENTAL,
                                                           .level_ = 1U,
                                                           .attack_ = 0U,
                                                           .defense_ = 0U,
                                                           .min_damage_ = 0U,
                                                           .max_damage_ = 0U,
                                                           .health_ = 0U,
                                                           .speed_ = 0U,
                                                           .counter_attack_ = 0U,
                                                           .growth_ = 0U,
                                                           .cost_ = 0U,
                                                           .fight_value_ = 100U,
                                                           .is_range_ = false,
                                                           .path_to_texture_ = "/path/folder/tex1" } };  // TODO

const inline std::array UNITS_PRESET_CASTLE = { UnitData{ .name_ = "pikeman",
                                                          .type_ = CastleUnitType::PIKEMAN,
                                                          .level_ = 1U,
                                                          .attack_ = 4U,
                                                          .defense_ = 5U,
                                                          .min_damage_ = 1U,
                                                          .max_damage_ = 3U,
                                                          .health_ = 10U,
                                                          .speed_ = 4U,
                                                          .counter_attack_ = 1U,
                                                          .growth_ = 14U,
                                                          .cost_ = 60U,
                                                          .fight_value_ = 100U,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex1" },
                                                UnitData{ .name_ = "archer",
                                                          .type_ = CastleUnitType::ARCHER,
                                                          .level_ = 2U,
                                                          .attack_ = 6U,
                                                          .defense_ = 3U,
                                                          .min_damage_ = 2U,
                                                          .max_damage_ = 3U,
                                                          .health_ = 10U,
                                                          .speed_ = 4U,
                                                          .counter_attack_ = 1U,
                                                          .growth_ = 9U,
                                                          .cost_ = 100U,
                                                          .fight_value_ = 115U,
                                                          .is_range_ = true,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "griffin",
                                                          .type_ = CastleUnitType::GRIFFIN,
                                                          .level_ = 3U,
                                                          .attack_ = 8U,
                                                          .defense_ = 8U,
                                                          .min_damage_ = 3U,
                                                          .max_damage_ = 6U,
                                                          .health_ = 25U,
                                                          .speed_ = 6U,
                                                          .counter_attack_ = 2U,
                                                          .growth_ = 7U,
                                                          .cost_ = 200U,
                                                          .fight_value_ = 324U,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "swordsman",
                                                          .type_ = CastleUnitType::SWORDSMAN,
                                                          .level_ = 4U,
                                                          .attack_ = 10U,
                                                          .defense_ = 12U,
                                                          .min_damage_ = 6U,
                                                          .max_damage_ = 9U,
                                                          .health_ = 35U,
                                                          .speed_ = 5U,
                                                          .counter_attack_ = 1U,
                                                          .growth_ = 4U,
                                                          .cost_ = 300U,
                                                          .fight_value_ = 445U,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "monk",
                                                          .type_ = CastleUnitType::MONK,
                                                          .level_ = 5U,
                                                          .attack_ = 12U,
                                                          .defense_ = 7U,
                                                          .min_damage_ = 10U,
                                                          .max_damage_ = 12U,
                                                          .health_ = 30U,
                                                          .speed_ = 5U,
                                                          .counter_attack_ = 1U,
                                                          .growth_ = 3U,
                                                          .cost_ = 400U,
                                                          .fight_value_ = 485U,
                                                          .is_range_ = true,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "cavalier",
                                                          .type_ = CastleUnitType::CAVALIER,
                                                          .level_ = 6U,
                                                          .attack_ = 15U,
                                                          .defense_ = 15U,
                                                          .min_damage_ = 15U,
                                                          .max_damage_ = 25U,
                                                          .health_ = 100U,
                                                          .speed_ = 7U,
                                                          .counter_attack_ = 1U,
                                                          .growth_ = 2U,
                                                          .cost_ = 1000U,
                                                          .fight_value_ = 1668U,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "angel",
                                                          .type_ = CastleUnitType::ANGEL,
                                                          .level_ = 7U,
                                                          .attack_ = 30U,
                                                          .defense_ = 30U,
                                                          .min_damage_ = 50U,
                                                          .max_damage_ = 50U,
                                                          .health_ = 200U,
                                                          .speed_ = 12U,
                                                          .counter_attack_ = 1U,
                                                          .growth_ = 1U,
                                                          .cost_ = 3000U,
                                                          .fight_value_ = 3585U,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex2" } };

inline const UnitData& getCastleUnit( CastleUnitType type ) {
  if ( type == CastleUnitType::COUNT ) {
    err::raise<std::runtime_error>( "index out of bounds" );
  }
  return UNITS_PRESET_CASTLE[static_cast<size_t>( type )];
}