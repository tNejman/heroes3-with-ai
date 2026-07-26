#include "Characters/Character.h"

void Character::initializeEquipment() {
  equipment_.emplace( EquipmentSlots::HELMET, nullptr );
  equipment_.emplace( EquipmentSlots::CAPE, nullptr );
  equipment_.emplace( EquipmentSlots::NECKLACE, nullptr );
  equipment_.emplace( EquipmentSlots::WEAPON, nullptr );
  equipment_.emplace( EquipmentSlots::SHIELD, nullptr );
  equipment_.emplace( EquipmentSlots::TORSO, nullptr );
  equipment_.emplace( EquipmentSlots::RING_1, nullptr );
  equipment_.emplace( EquipmentSlots::RING_2, nullptr );
  equipment_.emplace( EquipmentSlots::FEET, nullptr );
  equipment_.emplace( EquipmentSlots::MISC_1, nullptr );
  equipment_.emplace( EquipmentSlots::MISC_2, nullptr );
  equipment_.emplace( EquipmentSlots::MISC_3, nullptr );
  equipment_.emplace( EquipmentSlots::MISC_4, nullptr );
  equipment_.emplace( EquipmentSlots::MISC_5, nullptr );
};
void Character::initializeWarMachines() {
  war_machines_.emplace( "ballista", nullptr );
  war_machines_.emplace( "ammo_cart", nullptr );
  war_machines_.emplace( "first_aid_tent", nullptr );
  war_machines_.emplace( "catapult", nullptr );
}

std::optional<EquipmentSlots> Character::checkSlotIfEmpty( EquipmentSlots slot ) const {
  if ( slot == EquipmentSlots::RING ) {
    if ( equipment_.find( EquipmentSlots::RING_1 )->second == nullptr )
      return EquipmentSlots::RING_1;
    else if ( equipment_.find( EquipmentSlots::RING_2 )->second == nullptr ) {
      return EquipmentSlots::RING_2;
    } else {
      return std::nullopt;
    }
  }
  if ( slot == EquipmentSlots::MISC ) {
    for ( int i = 10; i < 15; ++i ) {
      EquipmentSlots actual_slot = static_cast<EquipmentSlots>( i );
      if ( equipment_.find( actual_slot )->second == nullptr )
        return actual_slot;
    }
    return std::nullopt;
  }

  if ( equipment_.find( slot )->second == nullptr )
    return slot;
  else
    return std::nullopt;
}

Character::Character(
    const std::string& name,
    const CoordPair coords,
    const uint32_t attack,
    const uint32_t defense,
    const uint32_t power,
    const uint32_t knowledge,
    const uint32_t max_mana,
    const short morale,
    const short luck ) : name_( name ),
                         alive_( true ),
                         coords_( coords ),
                         attack_( attack ),
                         defense_( defense ),
                         power_( power ),
                         knowledge_( knowledge ),
                         level_( 1 ),
                         experience_( 0 ),
                         max_mana_( max_mana ),
                         current_mana_( max_mana ),
                         morale_( morale ),
                         luck_( luck ) {
  initializeEquipment();
  initializeWarMachines();
};

Character::~Character() {}

const std::string& Character::getName() const {
  return this->name_;
}

bool Character::getIfUser() const {
  return this->is_user_character_;
}

void Character::setIfUser(bool is_user) {
  is_user_character_ = is_user;
}

uint32_t Character::getAttack() const {
  return this->attack_;
}

void Character::setAttack( const uint32_t new_attack ) {
  this->attack_ = new_attack;
}

void Character::modifyAttack( const uint32_t attack_diff ) {
  this->attack_ += attack_diff;
}

uint32_t Character::getDefense() const {
  return this->defense_;
}

void Character::setDefense( const uint32_t new_defense ) {
  this->defense_ = new_defense;
}

void Character::modifyDefense( const uint32_t defense_diff ) {
  this->defense_ += defense_diff;
}

uint32_t Character::getPower() const {
  return this->power_;
}

void Character::setPower( const uint32_t new_power ) {
  this->power_ = new_power;
}

void Character::modifyPower( const uint32_t power_diff ) {
  this->power_ += power_diff;
}

uint32_t Character::getKnowledge() const {
  return this->knowledge_;
}

void Character::setKnowledge( const uint32_t new_knowledge ) {
  this->knowledge_ = new_knowledge;
}

void Character::modifyKnowledge( const uint32_t knowledge_diff ) {
  this->knowledge_ += knowledge_diff;
}

uint32_t Character::getMovementPoints() const {
  return movement_points_;
}

void Character::setMovementPoints( const uint32_t new_movement ) {
  this->movement_points_ = new_movement;
}

void Character::modifyMovementPoints( const uint32_t movement_diff ) {
  this->movement_points_ += movement_diff;
}

uint32_t Character::getLevel() const {
  return this->level_;
}

void Character::levelUp() {
  this->level_++;
}

uint32_t Character::getExperience() const {
  return this->experience_;
}

void Character::gainExperience( const uint32_t experience ) {
  uint32_t old_level = this->level_;

  this->experience_ += experience;

  if ( this->experience_ >= EXPERIENCE_THRESHHOLDS[old_level + 1] ) {
    levelUp();
  }
}

uint32_t Character::getMaxMana() const {
  return this->max_mana_;
}
void Character::setMaxMana( const uint32_t new_max_mana ) {
  this->max_mana_ = new_max_mana;
}
void Character::modifyMaxMana( const uint32_t max_mana_diff ) {
  this->max_mana_ += max_mana_diff;
}

uint32_t Character::getCurrentMana() const {
  return this->current_mana_;
}
void Character::setCurrentMana( const uint32_t new_current_mana ) {
  this->current_mana_ = new_current_mana;
}
void Character::modifyCurrentMana( const uint32_t current_mana_diff ) {
  this->current_mana_ += current_mana_diff;
}

short Character::getMorale() const {
  return this->morale_;
}
void Character::setMorale( const short new_morale ) {
  this->morale_ = new_morale;
}
void Character::modifyMorale( const short morale_diff ) {
  this->morale_ += morale_diff;
}

short Character::getLuck() const {
  return this->luck_;
}
void Character::setLuck( const short new_luck ) {
  this->luck_ = new_luck;
}
void Character::modifyLuck( const short luck_diff ) {
  this->luck_ += luck_diff;
}

uint32_t Character::getEffectiveSpeed() {
  throw NotImplementedException("Character::getEffectiveSpeed");
  return 0;  // TODO
}

bool Character::getIfAlive() const {
  return this->alive_;
}

bool Character::getIfBackpackFull() const {
  return backpack_.size() == 64;
}

void Character::pickUpArtifact( std::unique_ptr<const Artifact> artifact ) {
  if ( this->getIfBackpackFull() ) {
    throw FullBackpackException( "Backpack full. Cannot pick up." );
  }
  backpack_.push_back( std::move( artifact ) );
}

void Character::equipArtifact( ArtifactType type, EquipmentSlots slot ) {
  std::optional<EquipmentSlots> slot_if_empty = this->checkSlotIfEmpty( slot );
  EquipmentSlots slot_specific;
  if ( !slot_if_empty.has_value() )
    throw NotEmptySlotException( "Cannot equip into a full slot" );
  else
    slot_specific = slot_if_empty.value();

  std::unique_ptr<const Artifact> artifact_temp = nullptr;
  for ( auto itr = backpack_.begin(); itr != backpack_.end(); ++itr ) {
    if ( ( *itr )->getType() != type ) {
      continue;
    } else if ( ( *itr )->getSlot() != slot ) {
      throw InvalidSlotException( "This artifact cannot be equipped into that slot" );

    } else {
      artifact_temp = std::move( *itr );
      backpack_.erase( itr );
      break;
    }
  }
  if ( artifact_temp == nullptr ) {
    throw InvalidArtifactTypeException( "No such artifact found in backpack" );
  }
  equipment_[slot_specific] = std::move( artifact_temp );
}

void Character::unequipArtifact( EquipmentSlots slot ) {
  if ( equipment_[slot] == nullptr )
    throw EmptySlotException( "This slot is empty. Cannot unequip." );
  if ( this->getIfBackpackFull() ) {
    throw FullBackpackException( "Backpack full. Cannot unequip." );
  }
  backpack_.push_back( std::move( equipment_[slot] ) );
  equipment_[slot].reset( nullptr );
}

void Character::recruitWarMachine( std::unique_ptr<const Ballista> war_machine ) {
  if ( war_machines_["ballista"] != nullptr )
    throw NotEmptySlotException( "This slot is not empty. Cannot recruit." );
  war_machines_["ballista"] = std::move( war_machine );
}
void Character::recruitWarMachine( std::unique_ptr<const AmmoCart> war_machine ) {
  if ( war_machines_["ammo_cart"] != nullptr )
    throw NotEmptySlotException( "This slot is not empty. Cannot recruit." );
  war_machines_["ammo_cart"] = std::move( war_machine );
}
void Character::recruitWarMachine( std::unique_ptr<const FirstAidTent> war_machine ) {
  if ( war_machines_["first_aid_tent"] != nullptr )
    throw NotEmptySlotException( "This slot is not empty. Cannot recruit." );
  war_machines_["first_aid_tent"] = std::move( war_machine );
}
void Character::recruitWarMachine( std::unique_ptr<const Catapult> war_machine ) {
  if ( war_machines_["catapult"] != nullptr )
    throw NotEmptySlotException( "This slot is not empty. Cannot recruit." );
  war_machines_["catapult"] = std::move( war_machine );
}
void Character::unequipWarMachine( const std::string& slot_name ) {
  if ( war_machines_[slot_name] == nullptr )
    throw EmptySlotException( "This slot is empty. Cannot unequip." );
  // TODO empty slot, drop machine
}

void Character::equipSpellBook( std::unique_ptr<SpellBook> spell_book ) {
  if ( this->spell_book_ == nullptr )
    throw NotEmptySlotException( "This slot is not empty. Cannot equip." );

  this->spell_book_ = std::move( spell_book );
}
std::unique_ptr<SpellBook> Character::unequipSpellBook() {
  std::unique_ptr<SpellBook> spell_book = std::move( this->spell_book_ );
  this->spell_book_.reset( nullptr );
  return spell_book;
}

const std::vector<std::unique_ptr<const Artifact>>& Character::getBackpack() {
  return this->backpack_;
}
std::array<std::shared_ptr<UnitStack>, MAX_PARTY_SIZE>& Character::getParty() {
  return this->party_;
}
uint32_t Character::getPartySize() {
  uint32_t party_count = 0;
  for ( const auto& mp : this->party_ ) {
    if ( mp != nullptr )
      ++party_count;
  }
  return party_count;
}

void Character::recruitUnitStack( std::shared_ptr<UnitStack> unit_stack ) {
  if ( getPartySize() == MAX_PARTY_SIZE ) {
    throw NotEmptySlotException( "No empty slot in Party to recuit a new unit" );
  }
  for ( auto& mp : this->party_ ) {
    if ( mp == nullptr ) {
      mp = std::move( unit_stack );
      return;
    }
  }
}
std::shared_ptr<Character> Character::copy() {
  std::shared_ptr<Character> copy =
      std::make_shared<Character>( this->name_, this->coords_, this->attack_, this->defense_, this->power_, this->knowledge_,
                                   this->max_mana_, this->morale_, this->luck_ );
  copy->alive_ = this->alive_;
  copy->level_ = this->level_;
  copy->experience_ = this->experience_;
  copy->current_mana_ = this->current_mana_;
  copy->movement_points_ = this->movement_points_;

  for ( uint32_t i = 0; i < SECONDARY_SKILLS_SLOTS_COUNT; ++i ) {
    if ( this->secondary_skills_[i] != nullptr ) {
      copy->secondary_skills_[i] = secondary_skills_[i]->copy();
    } else {
      copy->secondary_skills_[i] = nullptr;
    }
  }

  for ( const auto& [slot, artifact] : this->equipment_ ) {
    if ( artifact != nullptr ) {
      copy->equipment_[slot] = artifact->copy();
    } else {
      copy->equipment_[slot] = nullptr;
    }
  }

  for ( const auto& [slot, war_machine] : this->war_machines_ ) {
    if ( war_machine != nullptr ) {
      copy->war_machines_[slot] = war_machine->copy();
    } else {
      copy->war_machines_[slot] = nullptr;
    }
  }

  if ( this->spell_book_ != nullptr ) {
    copy->spell_book_ = this->spell_book_->copy();
  } else {
    copy->spell_book_ = nullptr;
  }

  for ( const auto& artifact : this->backpack_ ) {
    copy->backpack_.push_back( artifact->copy() );
  }

  for ( uint32_t i = 0; i < MAX_PARTY_SIZE; ++i ) {
    if ( this->party_[i] != nullptr ) {
      copy->party_[i] = this->party_[i]->copy();
    } else {
      copy->party_[i] = nullptr;
    }
  }
  return copy;
}
