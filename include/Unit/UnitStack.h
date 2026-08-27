#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy UnitStack:
  - Klasa jest obiektem reprezentującym oddział jednostki w grze. Posiada informacje o jednostce oraz jej ilości.
*/

#include <functional>

#include "Battle/TileObject.hpp"
#include "Miscellaneous/Coords.h"
#include "Unit/UnitsLib.h"

namespace {
constexpr inline int DEFAULT_UNIT_STACK_MORALE = 0;
constexpr inline int DEFAULT_UNIT_STACK_LUCK = 0;
}  // namespace

class UnitStack : public TileObject {
 private:
  // CoordPair coords_in_battle_{ 0, 0 };
  std::reference_wrapper<const UnitData> data_;
  int morale_ = DEFAULT_UNIT_STACK_MORALE;
  int luck_ = DEFAULT_UNIT_STACK_LUCK;
  int size_;
  int current_health_;
  CoordPair coords_in_battle_;

  // void checkUnit() const;

 public:
  UnitStack( UnitTypeV type, int size );
  [[nodiscard]] const UnitData& getData() const noexcept;

  [[nodiscard]] int getMorale() const noexcept;
  void setMorale( int new_morale ) noexcept;
  [[nodiscard]] int getLuck() const noexcept;
  void setLuck( int new_luck ) noexcept;
  [[nodiscard]] int getSize() const noexcept;

  [[nodiscard]] int getHealthPool() const noexcept;
  void modifyCurrentHealth( int health_diff ) noexcept;

  [[nodiscard]] bool isAlive() const noexcept;

  void setCoordsInBattle( CoordPair new_coords ) noexcept;
  [[nodiscard]] CoordPair getCoordsInBattle() const noexcept;

  [[nodiscard]] UnitStack* asUnit() noexcept override;
  // [[nodiscard]] uint32_t getSpeed() const;
  // [[nodiscard]] FactionType getFactionType() const;
  // [[nodiscard]] int getUnitType() const;
  // [[nodiscard]] uint32_t getRange() const;
  // [[nodiscard]] uint32_t getCurrentHealth() const;
  // void setCurrentHealth( uint32_t new_current_health ) noexcept;
  // [[nodiscard]] double getEffectiveFightValue() const;
  // [[nodiscard]] std::shared_ptr<const Unit> getUnit() const;
  // [[nodiscard]] bool getIfAlive() const;
  // [[nodiscard]] std::shared_ptr<UnitStack> copy() const;
};