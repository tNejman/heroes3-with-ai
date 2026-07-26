#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy UnitStack:
  - Klasa jest obiektem reprezentującym oddział jednostki w grze. Posiada informacje o jednostce oraz jej ilości.
*/

#include <cstdint>
#include <memory>

#include "Battle/TileObject.h"
#include "Miscellaneous/Coords.h"
#include "Unit/Unit.h"


class UnitStack : public TileObject {
 private:
  CoordPair coords_in_battle_ = CoordPair( 0u, 0u );
  std::shared_ptr<const Unit> unit_;
  short morale_;
  short luck_;
  uint32_t size_;
  uint32_t current_health_;

  void checkUnit() const;

 public:
  UnitStack( std::shared_ptr<const Unit> unit, uint32_t size );
  ~UnitStack() = default;
  void setCoordsInBattle( CoordPair new_coords );
  CoordPair getCoordsInBattle() const;
  uint32_t getSpeed() const;
  int getFactionType() const;
  int getUnitType() const;
  short getMorale() const;
  short getLuck() const;
  uint32_t getRange() const;
  uint32_t getSize() const;
  uint32_t getCurrentHealth() const;
  double getEffectiveFightValue() const;
  std::shared_ptr<const Unit> getUnit() const;
  bool modifyCurrentHealth( int health_diff );
  uint32_t getHealthPool() const;
  bool getIfAlive() const;
  std::shared_ptr<UnitStack> copy() const;
  void die();
};