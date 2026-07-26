#pragma once
// Autor: Tomasz Nejman i Naszkowski
/* Zawartość klasy Unit:
  - Klasa Unit odpowiada za jednostki w grze.
  - Zawiera metody do zarządzania statystykami jednostek, ich poziomem, obrażeniami i innymi parametrami.
*/
// #include <SFML/Graphics.hpp>

#include <stdint.h>

#include <iostream>
#include <string>

#include "Battle/TileObject.h"
#include "Exceptions/ExpiredWeakPtrException.hpp"
#include "Exceptions/InvalidUnitNameException.hpp"
#include "Exceptions/_NotImplementedException.hpp"
#include "Miscellaneous/Printable.h"
#include "Miscellaneous/ProjectLib.h"
#include "Miscellaneous/UnitsLib.h"
#include "Units/Faction.hpp"

class Unit : public TileObject, public Printable {
 protected:
  const std::shared_ptr<const UnitData> unit_data_;
  const std::weak_ptr<Faction> faction_;
  const int unit_type_;

 public:
  Unit( const std::shared_ptr<const UnitData> unit_data, const int unit_type );  // @Warning For use by WarMachines ONLY
  Unit( const std::shared_ptr<const UnitData> unit_data, const std::weak_ptr<Faction> faction, const int unit_type );
  ~Unit() = default;
  virtual sf::Texture& accept( Visitor& v ) const override { return v.visit( *this ); }
  const std::string& getName() const;
  uint32_t getLevel() const;
  uint32_t getAttack() const;
  uint32_t getDefense() const;
  uint32_t getMinDamage() const;
  uint32_t getMaxDamage() const;
  uint32_t getHealth() const;
  uint32_t getSpeed() const;
  uint32_t getCounterAttack() const;
  uint32_t getGrowth() const;
  uint32_t getCost() const;
  uint32_t getDmg() const;
  virtual uint32_t getRange() const;
  uint32_t getFightValue() const;

  const std::string& getPathToTexture() const;
  const std::weak_ptr<Faction> getFaction() const;
  int getUnitType() const;  /// @details cannot return Enum value, because Units belong to different facitons
};