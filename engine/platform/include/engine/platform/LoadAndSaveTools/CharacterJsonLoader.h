#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "engine/model/IGame/Coords.h"

#include "engine/Artifact/Artifact.h"
#include "engine/Character/Character.h"
#include "engine/Character/SecondarySkill.h"
#include "engine/Magic/SpellBook.h"
#include "engine/Unit/Unit.h"
#include "engine/Unit/UnitStack.h"
#include "engine/Unit/WarMachine.h"

class CharacterJsonLoader : public IJsonLoader<Character> {
 private:
  std::vector<std::shared_ptr<Faction>>& factions_;

  [[nodiscard]] std::shared_ptr<Character> doGetObject() noexcept override;

  [[nodiscard]] bool verifySaveMarker( const std::string& marker ) const noexcept;
  [[nodiscard]] std::string loadName() const noexcept;
  [[nodiscard]] CoordPair loadCoords() const noexcept;
  [[nodiscard]] bool loadAlive() const noexcept;
  [[nodiscard]] std::array<int, 4> loadPrimarySkills() const noexcept;
  [[nodiscard]] std::array<int, 7> loadMiscValues() const noexcept;
  [[nodiscard]] std::vector<std::unique_ptr<SecondarySkill>> loadSecondarySkills() const noexcept;
  [[nodiscard]] std::array<std::unique_ptr<const Artifact>, 14> loadArtifactsEquipped() const noexcept;
  [[nodiscard]] std::array<std::unique_ptr<WarMachine>, 4> loadWarMachines() const noexcept;
  [[nodiscard]] std::unique_ptr<SpellBook> loadSpells() const noexcept;
  [[nodiscard]] std::vector<std::unique_ptr<const Artifact>> loadArtifactsBackpack() const noexcept;
  [[nodiscard]] std::array<std::shared_ptr<UnitStack>, 7> loadParty() const noexcept;

 public:
  [[nodiscard]] CharacterJsonLoader( std::vector<std::shared_ptr<Faction>>& factions ) noexcept;
  ~CharacterJsonLoader() noexcept = default;
};