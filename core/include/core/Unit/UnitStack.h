#pragma once

#include <functional>

#include "engine/model/IGame/Coords.h"

#include "aux/Err.hpp"

#include "core/Battle/TileObject.hpp"
#include "core/Unit/UnitsLib.h"

class UnitStack : public TileObject {
 private:
  static constexpr int DEFAULT_UNIT_STACK_MORALE = 0;
  static constexpr int DEFAULT_UNIT_STACK_LUCK = 0;

  std::reference_wrapper<const UnitData> data_;
  int morale_ = DEFAULT_UNIT_STACK_MORALE;
  int luck_ = DEFAULT_UNIT_STACK_LUCK;
  int size_;
  int current_health_;
  CoordPair coords_in_battle_;

 public:
  [[nodiscard]] constexpr UnitStack( UnitTypeV type, int size ) noexcept;
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

  [[nodiscard]] const UnitStack* asUnit() const noexcept override;
  [[nodiscard]] UnitStack* asUnit() noexcept override;
};

/* ===== @CONSTEXPR IMPL ===== */

constexpr UnitStack::UnitStack( UnitTypeV type, int size ) noexcept
    : TileObject( false ),
      data_( getUnitDataFromType( type ) ),
      size_( size ),
      current_health_( data_.get().health_ ),
      coords_in_battle_( 0, 0 ) {
  err::passCondOrAbort( size > 0 );
};