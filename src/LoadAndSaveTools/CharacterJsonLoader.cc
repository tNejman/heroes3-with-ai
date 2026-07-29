#include "LoadAndSaveTools/CharacterJsonLoader.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

#include "Character/Character.h"
#include "Magic/SpellBook.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "Unit/UnitStack.h"
#include "Unit/WarMachine.h"

std::shared_ptr<Character> CharacterJsonLoader::doGetObject() {
  try {
    if ( !verifySaveMarker( data_["marker"] ) ) {
      std::string message;
      message += "CharacterJsonLoader expected json to begin with \"CHARACTER\" marker but instead read: ";
      message += data_["marker"];
      throw DamagedSaveException( message );
    }
    auto name = loadName();
    auto coords = loadCoords();
    auto if_alive = loadAlive();
    auto primary_skills = loadPrimarySkills();
    auto misc_values = loadMiscValues();
    auto secondary_skills = loadSecondarySkills();
    auto artifacts_equipped = loadArtifactsEquipped();
    auto war_machines = loadWarMachines();
    auto spell_book = loadSpells();
    auto artifacts_backpack = loadArtifactsBackpack();
    auto party = loadParty();

    uint32_t attack = primary_skills[0];
    uint32_t defense = primary_skills[1];
    uint32_t power = primary_skills[2];
    uint32_t knowledge = primary_skills[3];

    // uint32_t level = static_cast<uint32_t>( misc_values[0] );       // unused in constructor
    uint32_t experience = static_cast<uint32_t>( misc_values[1] );  // unused in constructor
    uint32_t max_mana = static_cast<uint32_t>( misc_values[2] );
    uint32_t current_mana = static_cast<uint32_t>( misc_values[3] );     // unused in constructor
    uint32_t movement_points = static_cast<uint32_t>( misc_values[4] );  // unused in constructor
    short morale = static_cast<short>( misc_values[5] );
    short luck = static_cast<short>( misc_values[6] );
    auto character =
        std::make_shared<Character>( name, coords, attack, defense, power, knowledge, max_mana, morale, luck );

    if ( !if_alive ) {
      character->die();
    }

    character->gainExperience( experience );

    character->setCurrentMana( current_mana );
    character->setMovementPoints( movement_points );

    for ( auto& sec_skill : secondary_skills ) {
      character->learnSecondarySkill( std::move( sec_skill ) );
    }

    for ( auto& artifact : artifacts_equipped ) {
      if ( artifact != nullptr ) {
        ArtifactType type = artifact->getType();
        EquipmentSlots slot = artifact->getSlot();
        character->pickUpArtifact( std::move( artifact ) );
        character->equipArtifact( type, slot );
      }
    }

    // auto make_character_recruit_war_machines = [&]<typename T>( std::unique_ptr<WarMachine> war_machine ) {
    //   if ( war_machine != nullptr ) {
    //     const T* raw_ptr = dynamic_cast<const T*>( war_machine.get() );
    //     if ( raw_ptr != nullptr ) {
    //       std::unique_ptr<const T> unq_ptr( const_cast<T*>( raw_ptr ) );
    //       war_machine.release();
    //       character->recruitWarMachine( std::move( unq_ptr ) );
    //     }
    //   }
    // };
    // make_character_recruit_war_machines.operator()<Ballista>( std::move( war_machines[0] ) );
    // make_character_recruit_war_machines.operator()<AmmoCart>( std::move( war_machines[1] ) );
    // make_character_recruit_war_machines.operator()<FirstAidTent>( std::move( war_machines[2] ) );
    // make_character_recruit_war_machines.operator()<Catapult>( std::move( war_machines[3] ) );
    auto* raw_ballista = war_machines[0].get();
    if ( raw_ballista != nullptr ) {
      std::unique_ptr<Ballista> ballista_ptr( dynamic_cast<Ballista*>( war_machines[0].release() ) );
      character->recruitWarMachine( std::move( ballista_ptr ) );
    }
    auto* raw_ammo_cart = war_machines[1].get();
    if ( raw_ammo_cart != nullptr ) {
      std::unique_ptr<AmmoCart> ammo_cart_ptr( dynamic_cast<AmmoCart*>( war_machines[1].release() ) );
      character->recruitWarMachine( std::move( ammo_cart_ptr ) );
    }
    auto* raw_first_aid_tent = war_machines[2].get();
    if ( raw_first_aid_tent != nullptr ) {
      std::unique_ptr<FirstAidTent> first_aid_tent_ptr( dynamic_cast<FirstAidTent*>( war_machines[2].release() ) );
      character->recruitWarMachine( std::move( first_aid_tent_ptr ) );
    }
    auto* raw_catapult = war_machines[3].get();
    if ( raw_catapult != nullptr ) {
      std::unique_ptr<Catapult> catapult_ptr( dynamic_cast<Catapult*>( war_machines[3].release() ) );
      character->recruitWarMachine( std::move( catapult_ptr ) );
    }

    character->equipSpellBook( std::move( spell_book ) );
    for ( auto& artifact_unq_ptr : artifacts_backpack ) {
      character->pickUpArtifact( std::move( artifact_unq_ptr ) );
    }
    for ( auto& unit_stack_ptr : party ) {
      character->recruitUnitStack( unit_stack_ptr );
    }

    throw NotImplementedException( "CharacterJsonLoader::doGetObject() is not finished" );
  } catch ( const std::exception& e ) {
    std::cout << "Error occured when creating Character from save: " << e.what() << std::endl;
    return nullptr;
  }
}

bool CharacterJsonLoader::verifySaveMarker( const std::string& marker ) const {
  return marker == CHARACTER_SAVE_START_MARKER;
}

std::string CharacterJsonLoader::loadName() const {
  return data_["name"];
}

CoordPair CharacterJsonLoader::loadCoords() const {
  uint32_t x = data_["coords"][0];
  uint32_t y = data_["coords"][1];
  return CoordPair( x, y );
}

bool CharacterJsonLoader::loadAlive() const {
  return data_["alive"];
}

std::array<uint32_t, 4> CharacterJsonLoader::loadPrimarySkills() const {
  std::array<uint32_t, 4> primary_skills{ data_["primary_skills"]["atk"], data_["primary_skills"]["def"],
                                          data_["primary_skills"]["pow"], data_["primary_skills"]["knwl"] };
  return primary_skills;
}

std::array<int, 7> CharacterJsonLoader::loadMiscValues() const {
  std::array<int, 7> misc_values{ data_["misc_values"]["lvl"],    data_["misc_values"]["exp"],
                                  data_["misc_values"]["mm"],     data_["misc_values"]["cm"],
                                  data_["misc_values"]["movpts"], data_["misc_values"]["mor"],
                                  data_["misc_values"]["lck"] };
  return misc_values;
}

std::vector<std::unique_ptr<SecondarySkill>> CharacterJsonLoader::loadSecondarySkills() const {
  std::vector<std::unique_ptr<SecondarySkill>> secondary_skills;
  for ( auto& sec_skill : data_["secondary_skills"] ) {
    int sec_skill_type = sec_skill[0];
    int sec_skill_level = sec_skill[1];

    auto sec_skill_type_s = static_cast<SecondarySkillType>( sec_skill_type );
    auto sec_skill_level_s = static_cast<SecondarySkillLevel>( sec_skill_level );
    secondary_skills.push_back( SecondarySkill::create( sec_skill_type_s, sec_skill_level_s ) );
  }
  return secondary_skills;
}

std::array<std::unique_ptr<const Artifact>, 14> CharacterJsonLoader::loadArtifactsEquipped() const {
  std::array<std::unique_ptr<const Artifact>, 14> artifacts;
  size_t i = 0;
  for ( const int artifact_type_int : data_["equipped_artifacts"] ) {
    if ( artifact_type_int == -1 ) {
      artifacts[i] = nullptr;
    } else {
      ArtifactType artifact_type = static_cast<ArtifactType>( artifact_type_int );
      artifacts[i] = Artifact::create( artifact_type );
    }
  }
  return artifacts;
}

std::array<std::unique_ptr<WarMachine>, 4> CharacterJsonLoader::loadWarMachines() const {
  std::array<std::unique_ptr<WarMachine>, 4> war_machines;
  size_t i = 0;
  for ( const int war_machine_type : data_["war_machines"] ) {
    switch ( war_machine_type ) {
      case -1: {
        war_machines[i] = nullptr;
        break;
      }
      case 0: {
        war_machines[i] = WarMachineFactory::createWarMachine( 0 );
        break;
      }
      case 1: {
        war_machines[i] = WarMachineFactory::createWarMachine( 1 );
        break;
      }
      case 2: {
        war_machines[i] = WarMachineFactory::createWarMachine( 2 );
        break;
      }
      case 3: {
        war_machines[i] = WarMachineFactory::createWarMachine( 3 );
        break;
      }
      default: {
        throw DamagedSaveException( "CharacterJsonLoader::loadWarMachines() encountered invalid war machine type: "
                                    + std::to_string( war_machine_type ) );
        break;
      }
    }
  }
  return war_machines;
}

std::unique_ptr<SpellBook> CharacterJsonLoader::loadSpells() const {
  std::vector<int> spell_ids = data_["spells"];
  if ( spell_ids.empty() ) {
    return nullptr;
  }
  auto spell_book = std::make_unique<SpellBook>();
  for ( const int spell_id : spell_ids ) {
    auto spell = Spell::create( static_cast<SpellType>( spell_id ) );
    if ( spell ) {
      spell_book->learnSpell( std::move( spell ) );
    }
  }
  return spell_book;
}

std::vector<std::unique_ptr<const Artifact>> CharacterJsonLoader::loadArtifactsBackpack() const {
  std::vector<std::unique_ptr<const Artifact>> artifacts;
  for ( const int artifact_type_int : data_["artifacts_backpack"] ) {
    ArtifactType artifact_type = static_cast<ArtifactType>( artifact_type_int );
    artifacts.push_back( Artifact::create( artifact_type ) );
  }
  return artifacts;
}

std::array<std::shared_ptr<UnitStack>, 7> CharacterJsonLoader::loadParty() const {
  std::array<std::shared_ptr<UnitStack>, 7> party;
  size_t i = 1;
  for ( auto& unit_stack : data_["party"] ) {
    FactionType faction_type = static_cast<FactionType>( unit_stack["faction"] );
    std::shared_ptr<const Unit> unit;
    switch ( faction_type ) {
      case FactionType::FORGE: {
        ForgeUnitType unit_type_forge = static_cast<ForgeUnitType>( unit_stack["unit_type"] );
        auto faction_forge = std::dynamic_pointer_cast<FactionForge>( factions_[FACTION_FORGE_ID_MARKER] );
        unit = faction_forge->getUnit( unit_type_forge );
        break;
      }
      case FactionType::CONFLUX: {
        ConfluxUnitType unit_type_conflux = static_cast<ConfluxUnitType>( unit_stack["unit_type"] );
        auto faction_conflux = std::dynamic_pointer_cast<FactionConflux>( factions_[FACTION_CONFLUX_ID_MARKER] );
        unit = faction_conflux->getUnit( unit_type_conflux );
        break;
      }
      case FactionType::CASTLE: {
        CastleUnitType unit_type_castle = static_cast<CastleUnitType>( unit_stack["unit_type"] );
        auto faction_castle = std::dynamic_pointer_cast<FactionCastle>( factions_[FACTION_CASTLE_ID_MARKER] );
        unit = faction_castle->getUnit( unit_type_castle );
        break;
      }
    }
    party[i] = std::make_shared<UnitStack>( unit, data_["party"]["unit" + std::to_string( i )]["size"] );
    party[i]->setMorale( data_["party"]["unit" + std::to_string( i )]["morale"] );
    party[i]->setLuck( data_["party"]["unit" + std::to_string( i )]["luck"] );
    party[i]->setSize( data_["party"]["unit" + std::to_string( i )]["size"] );
    party[i]->setCurrentHealth( data_["party"]["unit" + std::to_string( i )]["current_health"] );
  }
  return party;
}

CharacterJsonLoader::CharacterJsonLoader( std::vector<std::shared_ptr<Faction>>& factions ) : factions_( factions ) {
}