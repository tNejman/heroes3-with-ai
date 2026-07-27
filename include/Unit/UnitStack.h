#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy UnitStack:
  - Klasa jest obiektem reprezentującym oddział jednostki w grze. Posiada informacje o jednostce oraz jej ilości.
*/

#include <cstdint>
#include <memory>

#include "Battle/TileObject.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/UnitsLib.h"
#include "Unit/Unit.h"

class UnitStack : public TileObject {
 private:
  CoordPair coords_in_battle_ = CoordPair( 0U, 0U );
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
  [[nodiscard]] CoordPair getCoordsInBattle() const;
  [[nodiscard]] uint32_t getSpeed() const;
  [[nodiscard]] FactionType getFactionType() const;
  [[nodiscard]] int getUnitType() const;
  [[nodiscard]] short getMorale() const;
  void setMorale( short new_morale ) noexcept;
  [[nodiscard]] short getLuck() const;
  void setLick( short new_luck ) noexcept;
  [[nodiscard]] uint32_t getRange() const;
  [[nodiscard]] uint32_t getSize() const;
  void setSize( uint32_t new_size ) noexcept;
  [[nodiscard]] uint32_t getCurrentHealth() const;
  void setCurrentHealth( uint32_t new_current_health ) noexcept;
  [[nodiscard]] double getEffectiveFightValue() const;
  [[nodiscard]] std::shared_ptr<const Unit> getUnit() const;
  [[nodiscard]] bool modifyCurrentHealth( int health_diff );
  [[nodiscard]] uint32_t getHealthPool() const;
  [[nodiscard]] bool getIfAlive() const;
  [[nodiscard]] std::shared_ptr<UnitStack> copy() const;
  void die();
};