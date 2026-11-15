#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "engine/model/IGame/Coords.h"

#include "engine/platform/LoadAndSaveTools/ILoader.hpp"

#include "engine/Character/Character.h"

struct CharacterSaveContainer {
 public:
  std::optional<std::string> name_;
  std::optional<CoordPair> coords_;
  std::optional<bool> alive_;
  std::optional<std::array<uint32_t, 9>> stats_;
  std::optional<std::array<short, 2>> stats_2_;
  std::optional<std::array<std::pair<int, int>, 8>> secondary_skills_;
  std::optional<std::array<int, 14>> artifacts_equipped_;
  std::optional<std::array<int, 4>> war_machines_;
  std::optional<std::vector<std::pair<uint32_t, uint32_t>>> spells_;
  std::optional<std::vector<int>> artifacts_backpack_;
  std::optional<std::array<std::array<int, 6>, 7>> party_;
};

enum class CharacterDataLoadMode : char {
  NONE = -1,
  NAME = 0,
  COORDS = 1,
  ALIVE = 2,
  STATS1 = 3,
  STATS2 = 4,
  SECONDARY_SKILLS = 5,
  ARTIFACTS_EQUIPPED = 6,
  WAR_MACHINES = 7,
  SPELLS = 8,

  ARTIFACTS_BACKPACK = 9,
  PARTY = 10
};

class CharacterLoader : public ILoader<Character, CharacterSaveContainer> {
 private:
  CharacterDataLoadMode mode_ = CharacterDataLoadMode::NONE;
  void resetCounters() noexcept override;
  void moveWordToContainer( const int word ) noexcept override;
  [[nodiscard]] std::shared_ptr<Character> getObjectFromContainer() noexcept override;

  void incrementCounters() noexcept;
  [[nodiscard]] bool verifySaveMarker( const int word ) noexcept;
  void loadName( const int word ) noexcept;
  void loadCoords( const int word ) noexcept;
  void loadAlive( const int word ) noexcept;
  void loadStats1( const int word ) noexcept;
  void loadStats2( const int word ) noexcept;
  void loadSecondarySkills( const int word ) noexcept;
  void loadArtifactsEquipped( const int word ) noexcept;
  void loadWarMachines( const int word ) noexcept;
  void loadSpells( const int word ) noexcept;
  void loadArtifactsBackpack( const int word ) noexcept;

  void loadParty( const int word ) noexcept;

 public:
};