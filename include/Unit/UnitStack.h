#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy UnitStack:
  - Klasa jest obiektem reprezentującym oddział jednostki w grze. Posiada informacje o jednostce oraz jej ilości.
*/

#include <cstdint>
#include <functional>
#include <memory>

#include "Battle/TileObject.hpp"
#include "Miscellaneous/Coords.h"
#include "Unit/UnitsLib.h"

class UnitStack : public TileObject {
 private:
  CoordPair coords_in_battle_;
  std::reference_wrapper<const UnitData> data_;
  short morale_;
  short luck_;
  int size_;
  int current_health_;

  void checkUnit() const;

 public:
  UnitStack( const UnitData& unit, uint32_t size );
  UnitStack( const UnitStack& ) = delete;
  UnitStack( UnitStack&& ) noexcept = default;
  UnitStack& operator=( const UnitStack& ) = delete;
  UnitStack& operator=( UnitStack&& ) noexcept = default;
  ~UnitStack() = default;

  [[nodiscard]] const UnitData& getData() const noexcept;

  void setCoordsInBattle( CoordPair new_coords );
  [[nodiscard]] CoordPair getCoordsInBattle() const;
  // [[nodiscard]] uint32_t getSpeed() const;
  // [[nodiscard]] FactionType getFactionType() const;
  // [[nodiscard]] int getUnitType() const;
  // [[nodiscard]] short getMorale() const;
  // void setMorale( short new_morale ) noexcept;
  // [[nodiscard]] short getLuck() const;
  // void setLick( short new_luck ) noexcept;
  // [[nodiscard]] uint32_t getRange() const;
  // [[nodiscard]] uint32_t getSize() const;
  // void setSize( uint32_t new_size ) noexcept;
  // [[nodiscard]] uint32_t getCurrentHealth() const;
  void setCurrentHealth( uint32_t new_current_health ) noexcept;
  [[nodiscard]] double getEffectiveFightValue() const;
  // [[nodiscard]] std::shared_ptr<const Unit> getUnit() const;
  [[nodiscard]] bool modifyCurrentHealth( int health_diff );
  [[nodiscard]] int getHealthPool() const;
  [[nodiscard]] bool getIfAlive() const;
  [[nodiscard]] std::shared_ptr<UnitStack> copy() const;
};