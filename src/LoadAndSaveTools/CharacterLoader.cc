
#include "LoadAndSaveTools/CharacterLoader.h"

#include <memory>
#include <string>

#include "Character/Character.h"

CharacterSaveContainer::CharacterSaveContainer()
    : name_( std::nullopt ),
      coords_( std::nullopt ),
      alive_( std::nullopt ),
      stats_( std::nullopt ),
      stats_2_( std::nullopt ),
      secondary_skills_( std::nullopt ),
      artifacts_equipped_( std::nullopt ),
      war_machines_( std::nullopt ),
      spells_( std::nullopt ),
      artifacts_backpack_( std::nullopt ),
      party_( std::nullopt ) {
}

void CharacterLoader::resetCounters() {
}

void CharacterLoader::moveWordToContainer( const int word ) {
  std::string word_string = std::to_string( word );
  if ( word_string == "\n" ) {
    incrementCounters();
    return;
  }
  switch ( mode_ ) {
    case CharacterDataLoadMode::NONE:
      if ( !verifySaveMarker( word ) ) {
        throw DamagedSaveException( "CharacterLoader detected damaged save start marker: " + word );
      }
      break;
    case CharacterDataLoadMode::NAME: loadName( word ); break;
    case CharacterDataLoadMode::COORDS: loadCoords( word ); break;
    case CharacterDataLoadMode::ALIVE: loadAlive( word ); break;
    case CharacterDataLoadMode::STATS1: loadStats1( word ); break;
    case CharacterDataLoadMode::STATS2: loadStats2( word ); break;
    case CharacterDataLoadMode::SECONDARY_SKILLS: loadSecondarySkills( word ); break;
    case CharacterDataLoadMode::ARTIFACTS_EQUIPPED: loadArtifactsEquipped( word ); break;
    case CharacterDataLoadMode::WAR_MACHINES: loadWarMachines( word ); break;
    case CharacterDataLoadMode::SPELLS: loadSpells( word ); break;
    case CharacterDataLoadMode::ARTIFACTS_BACKPACK: loadArtifactsBackpack( word ); break;
    case CharacterDataLoadMode::PARTY: loadParty( word ); break;
  }
}

std::shared_ptr<Character> CharacterLoader::getObjectFromContainer() {
}

void CharacterLoader::incrementCounters() {
  int mode_int = static_cast<int>( mode_ );
  int new_mode_int;
  if ( mode_int == 10 ) {
    new_mode_int = -1;
  } else {
    new_mode_int = mode_int + 1;
  }
  mode_ = static_cast<CharacterDataLoadMode>( new_mode_int );
}

bool CharacterLoader::verifySaveMarker( const int word ) {
  return word == CHARACTER_SAVE_START_MARKER;
}

void CharacterLoader::loadName( const int word ) {
  static std::vector<int> name_as_int_vec;
  name_as_int_vec.push_back( word );
}

void CharacterLoader::loadCoords( const int word ) {
}

void CharacterLoader::loadAlive( const int word ) {
}

void CharacterLoader::loadStats1( const int word ) {
}

void CharacterLoader::loadStats2( const int word ) {
}

void CharacterLoader::loadSecondarySkills( const int word ) {
}

void CharacterLoader::loadArtifactsEquipped( const int word ) {
}

void CharacterLoader::loadWarMachines( const int word ) {
}

void CharacterLoader::loadSpells( const int word ) {
}

void CharacterLoader::loadArtifactsBackpack( const int word ) {
}

void CharacterLoader::loadParty( const int word ) {
}