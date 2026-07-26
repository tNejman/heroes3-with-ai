#pragma once
// Autor: Tomasz Nejman
/* zawartość klasy Faction:
  - Klasa Faction odpowiada za zarządzanie frakcjami w grze.
  - Zawiera metody do tworzenia jednostek, zarządzania dostępnością jednostek i ich typami.
*/
#include <array>
#include <memory>

#include "Miscellaneous/UnitsLib.h"
#include "Units/Unit.h"

/**
 * @Warning
 * Inheritance twice is purposeful here.
 * Faction cannot start as a template class because a handle
 * to complete interface is required.
 */
class Faction : public std::enable_shared_from_this<Faction> {
 private:
  FactionAttitude faction_attitude_;

 protected:
  std::array<std::shared_ptr<const Unit>, 7> available_units_ = {
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
  int faction_type_;
  std::weak_ptr<Faction> getWeakPtr() {
    return shared_from_this();
  }

 public:
  Faction( FactionAttitude faction_attitude ) : faction_attitude_( faction_attitude ) {}
  FactionAttitude getFactionAttitude() const {
    return this->faction_attitude_;
  }
  virtual std::string getName() const = 0;
  virtual int getFactionType() const = 0;
};

template <typename FactionUnitEnum>
class GenericFaction : public Faction {
 protected:
  const std::map<FactionUnitEnum, const std::shared_ptr<const UnitData>>& UNITS_PRESET_;

  std::shared_ptr<const Unit> createUnit( FactionUnitEnum faction_unit_type ) {
    const std::shared_ptr<const UnitData> unit_data = UNITS_PRESET_.find( faction_unit_type )->second;
    return std::make_shared<Unit>( std::move( unit_data ), getWeakPtr(), int( faction_unit_type ) );
  };

 public:
  GenericFaction( FactionAttitude faction_attitude, const std::map<FactionUnitEnum, const std::shared_ptr<const UnitData>>& units_preset ) : Faction::Faction( faction_attitude ), UNITS_PRESET_( units_preset ) {};

  const std::shared_ptr<const Unit> getUnit( FactionUnitEnum faction_unit_type ) {
    const auto unit_idx = uint32_t( faction_unit_type );
    if ( available_units_[unit_idx] == nullptr ) {
      available_units_[unit_idx] = createUnit( faction_unit_type );
    }
    return available_units_[unit_idx];
  }
  virtual std::string getName() const = 0;
  virtual int getFactionType() const = 0;
};

class FactionForge : public GenericFaction<ForgeUnitType> {
 public:
  FactionForge() : GenericFaction( FactionAttitude::EVIL, UNITS_PRESET_FORGE ) {};
  std::string getName() const override { return "forge"; }
  int getFactionType() const override { return int( FactionType::FORGE ); }
};

class FactionConflux : public GenericFaction<ConfluxUnitType> {
 public:
  FactionConflux() : GenericFaction( FactionAttitude::NEUTRAL, UNITS_PRESET_CONFLUX ) {};
  std::string getName() const override { return "conflux"; }
  int getFactionType() const override { return int( FactionType::CONFLUX ); }
};

class FactionCastle : public GenericFaction<CastleUnitType> {
 public:
  FactionCastle() : GenericFaction( FactionAttitude::GOOD, UNITS_PRESET_CASTLE ) {};
  std::string getName() const override { return "castle"; }
  int getFactionType() const override { return int( FactionType::CASTLE ); }
};