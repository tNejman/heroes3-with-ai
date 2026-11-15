#pragma once

#include "engine/platform/LoadAndSaveTools/ISaver.hpp"

#include "engine/Character/Character.h"

class CharacterSaver : public ISaver {
 private:
  const std::unique_ptr<const Character> c_;

  void saveStats( std::ofstream& out ) const noexcept;
  void saveSecondarySkills( std::ofstream& out ) const noexcept;
  void saveEquipment( std::ofstream& out ) const noexcept;
  void saveWarMachines( std::ofstream& out ) const noexcept;
  void saveSpellBook( std::ofstream& out ) const noexcept;
  void saveBackpack( std::ostream& out ) const noexcept;
  void saveParty( std::ofstream& out ) const noexcept;

  void doSave( std::ofstream& out ) const noexcept override;

 public:
  [[nodiscard]] CharacterSaver( const std::string&& path, std::unique_ptr<const Character> character ) noexcept;
};