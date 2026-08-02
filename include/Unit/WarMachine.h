#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy WarMachine:
  - Klasa WarMachine odpowiada za maszyny wojenne w grze.
  - Czyli trebusz, katapulta, balista, wóz amunicyjny i namiot medyczny.
*/

#include <memory>

#include "Miscellaneous/Equippable.h"
#include "Unit/Unit.h"
#include "Unit/UnitsLib.h"

class WarMachine : public Unit, public Equippable {
 public:
  WarMachine( const std::shared_ptr<const UnitData> unit_data, const int unit_type ) : Unit( unit_data, unit_type ) {};

  virtual std::unique_ptr<WarMachine> copy() const = 0;
};

class Ballista : public WarMachine {
 public:
  Ballista( const std::shared_ptr<const UnitData> unit_data, const int unit_type )
      : WarMachine( unit_data, unit_type ) {};

  std::unique_ptr<WarMachine> copy() const override {
    return std::make_unique<Ballista>( this->unit_data_, this->unit_type_ );
  }
};
class AmmoCart : public WarMachine {
 public:
  AmmoCart( const std::shared_ptr<const UnitData> unit_data, const int unit_type )
      : WarMachine( unit_data, unit_type ) {};

  std::unique_ptr<WarMachine> copy() const override {
    return std::make_unique<AmmoCart>( this->unit_data_, this->unit_type_ );
  }
};

class FirstAidTent : public WarMachine {
 public:
  FirstAidTent( const std::shared_ptr<const UnitData> unit_data, const int unit_type )
      : WarMachine( unit_data, unit_type ) {};

  std::unique_ptr<WarMachine> copy() const override {
    return std::make_unique<FirstAidTent>( this->unit_data_, this->unit_type_ );
  }
};

class Catapult : public WarMachine {
 public:
  Catapult( const std::shared_ptr<const UnitData> unit_data, const int unit_type )
      : WarMachine( unit_data, unit_type ) {};

  std::unique_ptr<WarMachine> copy() const override {
    return std::make_unique<Catapult>( this->unit_data_, this->unit_type_ );
  }
};