#pragma once
// Autor: Tomasz Nejman
/* zawartość:
    - klasa 'Character' implementuje obiekt postaci
    - postać zawiera:
      - statystyki
      - zdolności (secondary_skills_)
      - miejsca na artefakty (equipment_)
      - miejsca na maszyny bojowe (war_machines_)
      - nieużywane obecnie artefakty (backpack_)
      - podwładne jednostki (party_)
*/
// #include <SFML/Graphics.hpp>

#include <array>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "Artifacts/Artifact.h"
#include "Characters/SecondarySkill.h"
#include "Exceptions/EmptySlotException.hpp"
#include "Exceptions/FullBackpackException.hpp"
#include "Exceptions/InvalidSlotException.hpp"
#include "Exceptions/NotEmptySlotException.hpp"
#include "Magic/SpellBook.h"
#include "Miscellaneous/ProjectLib.h"
#include "Units/UnitStack.h"
#include "Units/WarMachine.h"
#include "WorldMap/MapObject.h"

class Character : public MapObject {
 private:
  // Coords already implemented in MapObject

  // Basic information
  const std::string name_;
  bool alive_;
  CoordPair coords_;
  bool is_user_character_ = true;

  // Primary Skills
  uint32_t attack_;
  uint32_t defense_;
  uint32_t power_;
  uint32_t knowledge_;

  // Miscellanous values
  uint32_t level_;
  uint32_t experience_;
  uint32_t max_mana_;
  uint32_t current_mana_;
  uint32_t movement_points_;
  short morale_;
  short luck_;

  std::array<std::unique_ptr<const SecondarySkill>, SECONDARY_SKILLS_SLOTS_COUNT> secondary_skills_{
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
  std::map<EquipmentSlots, std::unique_ptr<const Artifact>> equipment_;
  std::map<std::string, std::unique_ptr<const WarMachine>> war_machines_;
  std::unique_ptr<SpellBook> spell_book_ = nullptr;
  std::vector<std::unique_ptr<const Artifact>> backpack_;
  std::array<std::shared_ptr<UnitStack>, MAX_PARTY_SIZE> party_ = {
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

  void initializeEquipment();
  void initializeWarMachines();

  std::optional<EquipmentSlots> checkSlotIfEmpty( EquipmentSlots slot ) const;

 public:
  friend class CharacterSaver;
  //   Character() = default;
  //   Character(const Character&) = default;
  //   Character(Character&&) = default;
  Character(
      const std::string& name,
      const CoordPair coords,
      const uint32_t attack,
      const uint32_t defense,
      const uint32_t power,
      const uint32_t knowledge,
      const uint32_t max_mana,
      const short morale,
      const short luck );
  ~Character();
  virtual sf::Texture& accept( Visitor& v ) const override { return v.visit( *this ); }
  const std::string& getName() const;

  bool getIfUser() const;
  void setIfUser(bool is_user);

  uint32_t getAttack() const;
  void setAttack( const uint32_t new_attack );
  void modifyAttack( const uint32_t attack_diff );

  uint32_t getDefense() const;
  void setDefense( const uint32_t new_defense );
  void modifyDefense( const uint32_t defense_diff );

  uint32_t getPower() const;
  void setPower( const uint32_t new_power );
  void modifyPower( const uint32_t power_diff );

  uint32_t getKnowledge() const;
  void setKnowledge( const uint32_t new_knowledge );
  void modifyKnowledge( const uint32_t knowledge_diff );

  uint32_t getMovementPoints() const;
  void setMovementPoints( const uint32_t new_movement );
  void modifyMovementPoints( const uint32_t movement_diff );

  uint32_t getLevel() const;
  void levelUp();

  uint32_t getExperience() const;
  void gainExperience( const uint32_t experience );

  uint32_t getMaxMana() const;
  void setMaxMana( const uint32_t new_max_mana );
  void modifyMaxMana( const uint32_t max_mana_diff );

  uint32_t getCurrentMana() const;
  void setCurrentMana( const uint32_t new_current_mana );
  void modifyCurrentMana( const uint32_t current_mana_diff );

  short getMorale() const;
  void setMorale( const short new_morale );
  void modifyMorale( const short morale_diff );

  short getLuck() const;
  void setLuck( const short new_luck );
  void modifyLuck( const short luck_diff );

  uint32_t getEffectiveSpeed();

  bool getIfAlive() const;
//   bool die();

  bool getIfBackpackFull() const;

  void pickUpArtifact( std::unique_ptr<const Artifact> artifact );
  void equipArtifact( ArtifactType type, EquipmentSlots slot );
  void unequipArtifact( EquipmentSlots slot );

  void recruitWarMachine( std::unique_ptr<const Ballista> war_machine );
  void recruitWarMachine( std::unique_ptr<const AmmoCart> war_machine );
  void recruitWarMachine( std::unique_ptr<const FirstAidTent> war_machine );
  void recruitWarMachine( std::unique_ptr<const Catapult> war_machine );
  void unequipWarMachine( const std::string& slot_name );

  void equipSpellBook( std::unique_ptr<SpellBook> spell_book );
  std::unique_ptr<SpellBook> unequipSpellBook();

  const std::vector<std::unique_ptr<const Artifact>>& getBackpack();
  std::array<std::shared_ptr<UnitStack>, MAX_PARTY_SIZE>& getParty();
  uint32_t getPartySize();

  void recruitUnitStack( std::shared_ptr<UnitStack> unit_stack );
  //  std::unique_ptr<UnitStack>& getPartyMember(uint32_t backpack_id);

  //  void learnSpell( const std::unique_ptr<Spell>& spell );
  //  void forgetSpell( const std::unique_ptr<Spell>& spell );
  //  void castSpell( const std::unique_ptr<Spell>& spell );
  std::shared_ptr<Character> copy();
};
