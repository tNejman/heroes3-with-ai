#pragma once
// Autor: Tomasz Nejman i Naszkowski
/* Zawartość klasy Unit:
  - Klasa Unit odpowiada za jednostki w grze.
  - Zawiera metody do zarządzania statystykami jednostek, ich poziomem, obrażeniami i innymi parametrami.
*/
// #include <SFML/Graphics.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <cstdint>
#include <memory>
#include <string>

#include "Battle/TileObject.hpp"
#include "Graphics/Printable.h"
#include "Graphics/Visitor.h"
#include "Unit/UnitsLib.h"

class Faction;

class Unit : public TileObject, public Printable {
 protected:
  const std::shared_ptr<const UnitData> unit_data_;
  const std::weak_ptr<Faction> faction_;
  const int unit_type_;

 public:
  Unit( const std::shared_ptr<const UnitData> unit_data, const int unit_type );  // @Warning For use by WarMachines ONLY
  Unit( const std::shared_ptr<const UnitData> unit_data, const std::weak_ptr<Faction> faction, const int unit_type );
  sf::Texture& accept( Visitor& v ) const override {
    return v.visit( *this );
  }
  [[nodiscard]] const std::string& getName() const;
  [[nodiscard]] uint32_t getLevel() const;
  [[nodiscard]] uint32_t getAttack() const;
  [[nodiscard]] uint32_t getDefense() const;
  [[nodiscard]] uint32_t getMinDamage() const;
  [[nodiscard]] uint32_t getMaxDamage() const;
  [[nodiscard]] uint32_t getHealth() const;
  [[nodiscard]] uint32_t getSpeed() const;
  [[nodiscard]] uint32_t getCounterAttack() const;
  [[nodiscard]] uint32_t getGrowth() const;
  [[nodiscard]] uint32_t getCost() const;
  [[nodiscard]] uint32_t getDmg() const;
  [[nodiscard]] virtual uint32_t getRange() const;
  [[nodiscard]] uint32_t getFightValue() const;

  [[nodiscard]] const std::string& getPathToTexture() const;
  [[nodiscard]] const std::weak_ptr<Faction> getFaction() const;
  [[nodiscard]] int getUnitType()
      const;  /// @details cannot return Enum value, because Units belong to different facitons
};