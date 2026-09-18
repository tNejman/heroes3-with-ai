#pragma once
// Autor: Tomasz Nejman i Tomasz Naszkowski
/* Zawartość klasy unitlib:
    - klasa pozwala na przechowywanie jednostek
    - klasa pozwala na tworzenie jednostek
    - klasa pozwala na dodawanie jednostek do armii
*/
#include <array>
#include <cstddef>
#include <string>
#include <variant>

#include "aux/DisableCopyMoveStructHelper.hpp"
#include "aux/Err.hpp"
#include "aux/Overload.hpp"

enum class FactionAttitude : char { EVIL, NEUTRAL, GOOD };

enum class FactionType : char { FORGE, CONFLUX, CASTLE };

enum class ForgeUnitType : char {
  GRUNT = 0,
  CYBER_DEAD = 1,
  PYRO = 2,
  STINGER = 3,
  JUMP_SOLDIER = 4,
  TANK = 5,
  JUGGERNAUT = 6,
  COUNT = 7
};

enum class ConfluxUnitType : char {
  PIXIE = 0,
  AIR_ELEMENTAL = 1,
  WATER_ELEMENTAL = 2,
  FIRE_ELEMENTAL = 3,
  EARTH_ELEMENTAL = 4,
  PSYCHIC_ELEMENTAL = 5,
  FIREBIRD = 6,
  COUNT = 7,
};

enum class CastleUnitType : char {
  PIKEMAN = 0,
  ARCHER = 1,
  GRIFFIN = 2,
  SWORDSMAN = 3,
  MONK = 4,
  CAVALIER = 5,
  ANGEL = 6,
  COUNT = 7,
};

enum class WarMachineType : char { BALLISTA = 0, AMMO_CART = 1, FIRST_AID_TENT = 2, CATAPULT = 3, COUNT = 4 };

using UnitTypeV = std::variant<ForgeUnitType, ConfluxUnitType, CastleUnitType, WarMachineType>;

// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
struct UnitData {
  const std::string name_;
  const UnitTypeV type_;
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
                                                          .level_ = 1,
                                                          .attack_ = 0,
                                                          .defense_ = 0,
                                                          .min_damage_ = 0,
                                                          .max_damage_ = 0,
                                                          .health_ = 0,
                                                          .speed_ = 0,
                                                          .counter_attack_ = 0,
                                                          .growth_ = 0,
                                                          .cost_ = 0,
                                                          .fight_value_ = 100,
                                                          .is_range_ = true,
                                                          .path_to_texture_ = "/path/folder/tex1" },
                                                UnitData{ .name_ = "ammo cart",
                                                          .type_ = WarMachineType::AMMO_CART,
                                                          .level_ = 1,
                                                          .attack_ = 0,
                                                          .defense_ = 0,
                                                          .min_damage_ = 0,
                                                          .max_damage_ = 0,
                                                          .health_ = 0,
                                                          .speed_ = 0,
                                                          .counter_attack_ = 0,
                                                          .growth_ = 0,
                                                          .cost_ = 0,
                                                          .fight_value_ = 100,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "first aid tent",
                                                          .type_ = WarMachineType::FIRST_AID_TENT,
                                                          .level_ = 1,
                                                          .attack_ = 0,
                                                          .defense_ = 0,
                                                          .min_damage_ = 0,
                                                          .max_damage_ = 0,
                                                          .health_ = 0,
                                                          .speed_ = 0,
                                                          .counter_attack_ = 0,
                                                          .growth_ = 0,
                                                          .cost_ = 0,
                                                          .fight_value_ = 100,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex3" },
                                                UnitData{ .name_ = "catapult",
                                                          .type_ = WarMachineType::CATAPULT,
                                                          .level_ = 1,
                                                          .attack_ = 0,
                                                          .defense_ = 0,
                                                          .min_damage_ = 0,
                                                          .max_damage_ = 0,
                                                          .health_ = 0,
                                                          .speed_ = 0,
                                                          .counter_attack_ = 0,
                                                          .growth_ = 0,
                                                          .cost_ = 0,
                                                          .fight_value_ = 100,
                                                          .is_range_ = true,
                                                          .path_to_texture_ = "/path/folder/tex4" } };

// @Warning @deprecated
const inline std::array UNITS_PRESET_FORGE = { UnitData{ .name_ = "grunt",
                                                         .type_ = ForgeUnitType::GRUNT,
                                                         .level_ = 1,
                                                         .attack_ = 0,
                                                         .defense_ = 0,
                                                         .min_damage_ = 0,
                                                         .max_damage_ = 0,
                                                         .health_ = 0,
                                                         .speed_ = 0,
                                                         .counter_attack_ = 0,
                                                         .growth_ = 0,
                                                         .cost_ = 0,
                                                         .fight_value_ = 100,
                                                         .is_range_ = false,
                                                         .path_to_texture_ = "/path/folder/tex1" } };  // TODO

const inline std::array UNITS_PRESET_CONFLUX = { UnitData{ .name_ = "air elemental",
                                                           .type_ = ConfluxUnitType::AIR_ELEMENTAL,
                                                           .level_ = 1,
                                                           .attack_ = 0,
                                                           .defense_ = 0,
                                                           .min_damage_ = 0,
                                                           .max_damage_ = 0,
                                                           .health_ = 0,
                                                           .speed_ = 0,
                                                           .counter_attack_ = 0,
                                                           .growth_ = 0,
                                                           .cost_ = 0,
                                                           .fight_value_ = 100,
                                                           .is_range_ = false,
                                                           .path_to_texture_ = "/path/folder/tex1" } };  // TODO

const inline std::array UNITS_PRESET_CASTLE = { UnitData{ .name_ = "pikeman",
                                                          .type_ = CastleUnitType::PIKEMAN,
                                                          .level_ = 1,
                                                          .attack_ = 3,
                                                          .defense_ = 3,
                                                          .min_damage_ = 1,
                                                          .max_damage_ = 3,
                                                          .health_ = 10,
                                                          .speed_ = 3,
                                                          .counter_attack_ = 1,
                                                          .growth_ = 13,
                                                          .cost_ = 60,
                                                          .fight_value_ = 100,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex1" },
                                                UnitData{ .name_ = "archer",
                                                          .type_ = CastleUnitType::ARCHER,
                                                          .level_ = 2,
                                                          .attack_ = 3,
                                                          .defense_ = 3,
                                                          .min_damage_ = 2,
                                                          .max_damage_ = 3,
                                                          .health_ = 10,
                                                          .speed_ = 3,
                                                          .counter_attack_ = 1,
                                                          .growth_ = 9,
                                                          .cost_ = 100,
                                                          .fight_value_ = 113,
                                                          .is_range_ = true,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "griffin",
                                                          .type_ = CastleUnitType::GRIFFIN,
                                                          .level_ = 3,
                                                          .attack_ = 8,
                                                          .defense_ = 8,
                                                          .min_damage_ = 3,
                                                          .max_damage_ = 3,
                                                          .health_ = 23,
                                                          .speed_ = 3,
                                                          .counter_attack_ = 2,
                                                          .growth_ = 7,
                                                          .cost_ = 200,
                                                          .fight_value_ = 323,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "swordsman",
                                                          .type_ = CastleUnitType::SWORDSMAN,
                                                          .level_ = 3,
                                                          .attack_ = 10,
                                                          .defense_ = 12,
                                                          .min_damage_ = 3,
                                                          .max_damage_ = 9,
                                                          .health_ = 33,
                                                          .speed_ = 3,
                                                          .counter_attack_ = 1,
                                                          .growth_ = 3,
                                                          .cost_ = 300,
                                                          .fight_value_ = 443,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "monk",
                                                          .type_ = CastleUnitType::MONK,
                                                          .level_ = 3,
                                                          .attack_ = 12,
                                                          .defense_ = 7,
                                                          .min_damage_ = 10,
                                                          .max_damage_ = 12,
                                                          .health_ = 30,
                                                          .speed_ = 3,
                                                          .counter_attack_ = 1,
                                                          .growth_ = 3,
                                                          .cost_ = 400,
                                                          .fight_value_ = 483,
                                                          .is_range_ = true,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "cavalier",
                                                          .type_ = CastleUnitType::CAVALIER,
                                                          .level_ = 3,
                                                          .attack_ = 13,
                                                          .defense_ = 13,
                                                          .min_damage_ = 13,
                                                          .max_damage_ = 23,
                                                          .health_ = 100,
                                                          .speed_ = 7,
                                                          .counter_attack_ = 1,
                                                          .growth_ = 2,
                                                          .cost_ = 1000,
                                                          .fight_value_ = 1668,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex2" },
                                                UnitData{ .name_ = "angel",
                                                          .type_ = CastleUnitType::ANGEL,
                                                          .level_ = 7,
                                                          .attack_ = 30,
                                                          .defense_ = 30,
                                                          .min_damage_ = 50,
                                                          .max_damage_ = 50,
                                                          .health_ = 200,
                                                          .speed_ = 12,
                                                          .counter_attack_ = 1,
                                                          .growth_ = 1,
                                                          .cost_ = 3000,
                                                          .fight_value_ = 3583,
                                                          .is_range_ = false,
                                                          .path_to_texture_ = "/path/folder/tex2" } };

inline const UnitData& getUnitDataFromType( UnitTypeV type ) {
  return std::visit( Overload{ [&]( ForgeUnitType t ) -> const UnitData& {
                                err::passCondOrAbort( t != ForgeUnitType::COUNT );
                                return UNITS_PRESET_FORGE[static_cast<size_t>( t )];
                              },
                               [&]( ConfluxUnitType t ) -> const UnitData& {
                                 err::passCondOrAbort( t != ConfluxUnitType::COUNT );
                                 return UNITS_PRESET_CONFLUX[static_cast<size_t>( t )];
                               },
                               [&]( CastleUnitType t ) -> const UnitData& {
                                 err::passCondOrAbort( t != CastleUnitType::COUNT );
                                 return UNITS_PRESET_CASTLE[static_cast<size_t>( t )];
                               },
                               [&]( WarMachineType t ) -> const UnitData& {
                                 err::passCondOrAbort( t != WarMachineType::COUNT );
                                 return WAR_MACHINES_PRESET[static_cast<size_t>( t )];
                               } },
                     type );
}