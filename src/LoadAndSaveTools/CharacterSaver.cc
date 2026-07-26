#include "LoadAndSaveTools/CharacterSaver.h"

// TODO fix to save enum instead of Name

void CharacterSaver::saveStats( std::ofstream& out ) const {
  out << "CHARACTER" << std::endl;
  out << c_->getName() << std::endl;
  out << c_->getCoords().x_ << ',' << c_->getCoords().y_ << std::endl;
  out << ( c_->getIfAlive() ? '1' : '0' ) << std::endl;
  out << c_->getAttack() << ',' << c_->getDefense() << ',' << c_->getPower() << ',' << c_->getKnowledge() << std::endl;
  out << c_->getLevel() << ',' << c_->getExperience() << ',' << c_->getMaxMana() << ',' << c_->getCurrentMana() << ',' << c_->getMovementPoints() << std::endl;
  out << c_->getMorale() << ',' << c_->getLuck() << std::endl;
}

void CharacterSaver::saveSecondarySkills( std::ofstream& out ) const {
  // out << "DEBUG: Secondary skills" << std::endl;
  for ( const auto& secondary_skill_ptr : c_->secondary_skills_ ) {
    if ( secondary_skill_ptr == nullptr )
      out << "-1,-1,";
    else {
      out << int( secondary_skill_ptr->getType() ) << ',';
      out << int( secondary_skill_ptr->getLevel() ) << ',';
    }
  }
  out << std::endl;
}

void CharacterSaver::saveEquipment( std::ofstream& out ) const {
  // out << "DEBUG: Artifacts" << std::endl;
  for ( const auto& [_, artifact_ptr] : c_->equipment_ ) {
    if ( artifact_ptr == nullptr )
      out << "-1,";
    else
      out << int( artifact_ptr->getType() ) << ',';
  }
  out << std::endl;
}

void CharacterSaver::saveWarMachines( std::ofstream& out ) const {
  // out << "DEBUG: War Machines" << std::endl;
  for ( const auto& [_, war_machine_ptr] : c_->war_machines_ ) {
    if ( war_machine_ptr == nullptr )
      out << -1 << ',';
    else
      out << war_machine_ptr->getName() << ',';
  }
  out << std::endl;
}

void CharacterSaver::saveSpellBook( std::ofstream& out ) const {
  // out << "DEBUG: SpellBook" << std::endl;
  if ( c_->spell_book_ == nullptr )
    out << -2 << std::endl;
  else {
    for ( const auto& spell_ptr : c_->spell_book_->spells_ ) {
      out << int( spell_ptr->getType() ) << ',';
      out << int( spell_ptr->getLevel() ) << ',';
    }
  }
}

void CharacterSaver::saveBackpack( std::ostream& out ) const {
  // out << "DEBUG: Backpack" << std::endl;
  if ( c_->backpack_.size() == 0 ) {
    out << -2 << std::endl;
    return;
  }

  for ( const auto& artifact_ptr : c_->backpack_ ) {
    out << int( artifact_ptr->getType() ) << ',';
  }
  out << std::endl;
}

void CharacterSaver::saveParty( std::ofstream& out ) const {
  // out << "DEBUG: Party" << std::endl;
  for ( const auto& unit_stack_ptr : c_->party_ ) {
    if ( unit_stack_ptr == nullptr ) {
      out << "-1,-1,-1,-1,-1,-1,";
    } else {
      out << unit_stack_ptr->getFactionType() << ',';
      out << unit_stack_ptr->getUnitType() << ',';
      out << unit_stack_ptr->getMorale() << ',';
      out << unit_stack_ptr->getLuck() << ',';
      out << unit_stack_ptr->getSize() << ',';
      out << unit_stack_ptr->getCurrentHealth() << ',';
    }
  }
  out << std::endl;
}

CharacterSaver::CharacterSaver( const std::string&& path, std::unique_ptr<const Character> character ) : ISaver( path ), c_( std::move( character ) ) {}

void CharacterSaver::doSave( std::ofstream& out ) const {
  this->saveStats( out );
  this->saveSecondarySkills( out );
  this->saveEquipment( out );
  this->saveWarMachines( out );
  this->saveSpellBook( out );
  this->saveBackpack( out );
}