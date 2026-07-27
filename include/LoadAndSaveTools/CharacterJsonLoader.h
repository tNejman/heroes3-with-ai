#pragma once

#include "Character/Character.h"
#include "LoadAndSaveTools/IJsonLoader.hpp"

class CharacterJsonLoader : public IJsonLoader<Character> {
 private:
  std::vector<std::shared_ptr<Faction>>& factions_;

  std::shared_ptr<Character> doGetObject() override;

  bool verifySaveMarker( const std::string& marker );
  std::string loadName();
  CoordPair loadCoords();
  bool loadAlive();
  std::array<int, 4> loadPrimarySkills();
  std::array<int, 7> loadMiscValues();
  std::vector<std::unique_ptr<SecondarySkill>> loadSecondarySkills();
  std::array<std::unique_ptr<const Artifact>, 14> loadArtifactsEquipped();
  std::array<std::unique_ptr<WarMachine>, 4> loadWarMachines();
  std::unique_ptr<SpellBook> loadSpells();
  std::vector<std::unique_ptr<const Artifact>> loadArtifactsBackpack();
  std::array<std::shared_ptr<UnitStack>, 7> loadParty();

 public:
  CharacterJsonLoader( std::vector<std::shared_ptr<Faction>>& factions );
  ~CharacterJsonLoader() = default;
};