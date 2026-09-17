#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "engine/Artifact/Artifact.h"
#include "engine/Character/Character.h"
#include "engine/Character/SecondarySkill.h"
#include "engine/Magic/SpellBook.h"
#include "core/Misc/Coords.h"
#include "engine/Unit/Unit.h"
#include "engine/Unit/UnitStack.h"
#include "engine/Unit/WarMachine.h"

class CharacterJsonLoader : public IJsonLoader<Character> {
 private:
  std::vector<std::shared_ptr<Faction>>& factions_;

  std::shared_ptr<Character> doGetObject() override;

  [[nodiscard]] bool verifySaveMarker( const std::string& marker ) const;
  [[nodiscard]] std::string loadName() const;
  [[nodiscard]] CoordPair loadCoords() const;
  [[nodiscard]] bool loadAlive() const;
  [[nodiscard]] std::array<int, 4> loadPrimarySkills() const;
  [[nodiscard]] std::array<int, 7> loadMiscValues() const;
  [[nodiscard]] std::vector<std::unique_ptr<SecondarySkill>> loadSecondarySkills() const;
  [[nodiscard]] std::array<std::unique_ptr<const Artifact>, 14> loadArtifactsEquipped() const;
  [[nodiscard]] std::array<std::unique_ptr<WarMachine>, 4> loadWarMachines() const;
  [[nodiscard]] std::unique_ptr<SpellBook> loadSpells() const;
  [[nodiscard]] std::vector<std::unique_ptr<const Artifact>> loadArtifactsBackpack() const;
  [[nodiscard]] std::array<std::shared_ptr<UnitStack>, 7> loadParty() const;

 public:
  CharacterJsonLoader( std::vector<std::shared_ptr<Faction>>& factions );
  ~CharacterJsonLoader() = default;
};