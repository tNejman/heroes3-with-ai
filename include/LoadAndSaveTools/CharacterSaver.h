#pragma once

#include "Characters/Character.h"
#include "LoadAndSaveTools/ISaver.hpp"

class CharacterSaver : public ISaver {
 private:
  const std::unique_ptr<const Character> c_;

  void saveStats( std::ofstream& out ) const;
  void saveSecondarySkills( std::ofstream& out ) const;
  void saveEquipment( std::ofstream& out ) const;
  void saveWarMachines( std::ofstream& out ) const;
  void saveSpellBook( std::ofstream& out ) const;
  void saveBackpack( std::ostream& out ) const;
  void saveParty( std::ofstream& out ) const;

  void doSave( std::ofstream& out ) const override;

 public:
  CharacterSaver( const std::string&& path, std::unique_ptr<const Character> character );
};