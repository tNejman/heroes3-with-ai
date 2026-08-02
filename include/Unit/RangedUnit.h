#pragma once
// Autor: Tomasz Nejman i Naszkowski
/* Zawartość klasy RangedUnit:
  - Klasa RangedUnit dziedziczy po klasie Unit i reprezentuje jednostki dystansowe w grze.
*/

#include <cstdint>
#include <memory>

#include "Unit/Faction.hpp"
#include "Unit/Unit.h"
#include "Unit/UnitsLib.h"

class RangedUnit : public Unit {
 private:
  uint32_t range_;
  // uint32_t shots_;

 public:
  // RangedUnit( const std::weak_ptr<Faction> faction,
  //             const std::string& name,
  //             const uint32_t level,
  //             const uint32_t attack,
  //             const uint32_t defense,
  //             const uint32_t min_damage,
  //             const uint32_t max_damage,
  //             const uint32_t range,
  //             const uint32_t shots,
  //             const uint32_t health,
  //             const uint32_t speed,
  //             const uint32_t counter_attack,
  //             const uint32_t growth,
  //             const uint32_t cost,
  //             const std::string path_to_texture) :
  //               Unit(faction, name, level, attack, defense,
  //                     min_damage, max_damage, health, speed, counter_attack,
  //                     growth, cost, path_to_texture) {
  //   range_ = range;
  //   shots_ = shots;
  // };
  RangedUnit( const std::shared_ptr<const UnitData> unit_data, const std::weak_ptr<Faction> faction,
              const int unit_type, uint32_t range )
      : Unit( unit_data, faction, unit_type ), range_( range ) {};
  virtual uint32_t getRange() const override;
};