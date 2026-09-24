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

#include <array>
#include <memory>
#include <optional>
#include <string>

#include "core/Artifact/Artifact.h"
#include "core/Character/Army.h"
#include "core/Character/Inventory.h"
#include "core/Character/Stats.h"
#include "core/Character/SecondarySkill.h"
#include "core/Magic/SpellBook.h"
#include "core/MapObject/MapObject.h"
#include "core/Misc/ProjectLib.h"
#include "engine/IGame/Coords.h"


constexpr inline int SECONDARY_SKILLS_SLOTS_COUNT = 8;

class Character : public MapObject {
 private:
  CharacterMoveDirection orientation_ = CharacterMoveDirection::RIGHT;
  const CharacterType character_type_ = CharacterType::FIRE_HERO;

  const int id_;

  const std::string name_;
  bool is_user_character_;  // TODO change to const

  character::Stats stats_;
  character::Inventory inventory_;
  character::Army army_;

  std::array<std::optional<SecondarySkill>, SECONDARY_SKILLS_SLOTS_COUNT> secondary_skills_;
  std::optional<SpellBook> spell_book_ = std::nullopt;

 public:
  // friend class CharacterSaver;
  Character() = delete;
  Character( const Character& ) = delete;
  Character( Character&& ) = default;
  Character( int id, std::string name, CoordPair coords, character::Stats stats, bool is_user ) noexcept;
  ~Character() override = default;
  Character& operator=( const Character& ) = delete;
  Character& operator=( Character&& ) = delete;
  void accept( Visitor& v ) const override;

  [[nodiscard]] int getId() const noexcept;

  [[nodiscard]] Character* asCharacter() noexcept override;

  [[nodiscard]] CharacterMoveDirection getOrientation() const;
  void setOrientation( CharacterMoveDirection new_orientation );

  [[nodiscard]] CharacterType getCharacterType() const;

  [[nodiscard]] const std::string& getName() const;

  [[nodiscard]] bool getIfUser() const;
  void setIfUser( bool is_user );

  [[nodiscard]] const character::Stats& stats() const noexcept;
  [[nodiscard]] character::Stats& stats() noexcept;
  [[nodiscard]] const character::Inventory& inventory() const noexcept;
  [[nodiscard]] character::Inventory& inventory() noexcept;
  [[nodiscard]] const character::Army& army() const noexcept;
  [[nodiscard]] character::Army& army() noexcept;

  // [[nodiscard]] uint32_t getEffectiveSpeed();

  // [[nodiscard]] bool getIfBackpackFull() const;

  // void pickUpArtifact( Artifact artifact );
  // void equipArtifact( artifact::Type type, EquipmentSlots slot );
  // void unequipArtifact( EquipmentSlots slot );

  // void recruitWarMachine( std::unique_ptr<const Ballista> war_machine );
  // void recruitWarMachine( std::unique_ptr<const AmmoCart> war_machine );
  // void recruitWarMachine( std::unique_ptr<const FirstAidTent> war_machine );
  // void recruitWarMachine( std::unique_ptr<const Catapult> war_machine );
  // void unequipWarMachine( const std::string& slot_name );

  void equipSpellBook( SpellBook spell_book );
  // [[nodiscard]] SpellBook unequipSpellBook();

  // const std::vector<Artifact>& getBackpack();
  // std::array<std::shared_ptr<UnitStack>, MAX_PARTY_SIZE>& getParty();
  // uint32_t getPartySize();

  // void recruitUnitStack( std::shared_ptr<UnitStack> unit_stack );
  //  std::unique_ptr<UnitStack>& getPartyMember(uint32_t backpack_id);

  //  void learnSpell( const std::unique_ptr<Spell>& spell );
  //  void forgetSpell( const std::unique_ptr<Spell>& spell );
  //  void castSpell( const std::unique_ptr<Spell>& spell );
  [[nodiscard]] std::shared_ptr<Character> copy() const noexcept;
};