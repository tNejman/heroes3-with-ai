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

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <array>
#include <memory>
#include <optional>
#include <string>

#include "Artifact/Artifact.h"
#include "Character/CharacterArmy.h"
#include "Character/CharacterInventory.h"
#include "Character/CharacterStats.h"
#include "Character/SecondarySkill.h"
#include "Magic/SpellBook.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

constexpr inline int SECONDARY_SKILLS_SLOTS_COUNT = 8;

class Character : public MapObject {
 private:
  CharacterMoveDirection orientation_ = CharacterMoveDirection::RIGHT;
  const CharacterType character_type_ = CharacterType::FIRE_HERO;

  std::string name_;
  bool is_user_character_;

  CharacterStats stats_;
  CharacterInventory inventory_;
  CharacterArmy army_;

  std::array<std::optional<SecondarySkill>, SECONDARY_SKILLS_SLOTS_COUNT> secondary_skills_;
  std::optional<SpellBook> spell_book_ = std::nullopt;

 public:
  // friend class CharacterSaver;
  Character() = delete;
  Character( const Character& ) = delete;
  Character( Character&& ) = delete;
  Character( std::string name, CoordPair coords, CharacterStats stats );
  ~Character() override = default;
  Character& operator=( const Character& ) = delete;
  Character& operator=( Character&& ) = delete;
  sf::Texture& accept( Visitor& v ) const override;

  [[nodiscard]] CharacterMoveDirection getOrientation() const;
  void setOrientation( CharacterMoveDirection new_orientation );

  [[nodiscard]] CharacterType getCharacterType() const;

  [[nodiscard]] const std::string& getName() const;

  [[nodiscard]] bool getIfUser() const;
  void setIfUser( bool is_user );

  [[nodiscard]] const CharacterStats& stats() const noexcept;
  [[nodiscard]] CharacterStats& stats() noexcept;
  [[nodiscard]] const CharacterInventory& inventory() const noexcept;
  [[nodiscard]] CharacterInventory& inventory() noexcept;
  [[nodiscard]] const CharacterArmy& army() const noexcept;
  [[nodiscard]] CharacterArmy& army() noexcept;

  // [[nodiscard]] uint32_t getEffectiveSpeed();

  // [[nodiscard]] bool getIfBackpackFull() const;

  // void pickUpArtifact( Artifact artifact );
  // void equipArtifact( ArtifactType type, EquipmentSlots slot );
  // void unequipArtifact( EquipmentSlots slot );

  // void recruitWarMachine( std::unique_ptr<const Ballista> war_machine );
  // void recruitWarMachine( std::unique_ptr<const AmmoCart> war_machine );
  // void recruitWarMachine( std::unique_ptr<const FirstAidTent> war_machine );
  // void recruitWarMachine( std::unique_ptr<const Catapult> war_machine );
  // void unequipWarMachine( const std::string& slot_name );

  void equipSpellBook( SpellBook spell_book );
  SpellBook unequipSpellBook();

  // const std::vector<Artifact>& getBackpack();
  // std::array<std::shared_ptr<UnitStack>, MAX_PARTY_SIZE>& getParty();
  // uint32_t getPartySize();

  // void recruitUnitStack( std::shared_ptr<UnitStack> unit_stack );
  //  std::unique_ptr<UnitStack>& getPartyMember(uint32_t backpack_id);

  //  void learnSpell( const std::unique_ptr<Spell>& spell );
  //  void forgetSpell( const std::unique_ptr<Spell>& spell );
  //  void castSpell( const std::unique_ptr<Spell>& spell );
  std::shared_ptr<Character> copy();
};