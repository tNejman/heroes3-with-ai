#include "Character/Character.h"

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "Artifact/Artifact.h"
#include "Character/CharacterArmy.h"
#include "Character/CharacterInventory.h"
#include "Character/CharacterStats.h"
#include "Exceptions/EmptySlotException.hpp"
#include "Exceptions/Err.hpp"
#include "Exceptions/NotEmptySlotException.hpp"
#include "Magic/SpellBook.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

Character::Character( std::string name, CoordPair coords, CharacterStats stats )
    : MapObject( coords ), name_( std::move( name ) ), is_user_character_( true ), stats_( std::move( stats ) ) {};

sf::Texture& Character::accept( Visitor& v ) const {
  return v.visit( *this );
}

CharacterMoveDirection Character::getOrientation() const {
  return this->orientation_;
}

void Character::setOrientation( CharacterMoveDirection new_orientation ) {
  this->orientation_ = new_orientation;
}

CharacterType Character::getCharacterType() const {
  return this->character_type_;
}

const std::string& Character::getName() const {
  return this->name_;
}

bool Character::getIfUser() const {
  return this->is_user_character_;
}

void Character::setIfUser( bool is_user ) {
  is_user_character_ = is_user;
}

[[nodiscard]] const CharacterStats& Character::stats() const noexcept {
  return stats_;
}

[[nodiscard]] CharacterStats& Character::stats() noexcept {
  return stats_;
}

[[nodiscard]] const CharacterInventory& Character::inventory() const noexcept {
  return inventory_;
}

[[nodiscard]] CharacterInventory& Character::inventory() noexcept {
  return inventory_;
}

[[nodiscard]] const CharacterArmy& Character::army() const noexcept {
  return army_;
}

[[nodiscard]] CharacterArmy& Character::army() noexcept {
  return army_;
}

// uint32_t Character::getEffectiveSpeed() {
//   err::raise<NotImplementedException>( "" );
//   return 0;  // TODO
// }

// bool Character::getIfBackpackFull() const {
//   return backpack_.size() == 64;
// }

// void Character::pickUpArtifact( Artifact artifact ) {
//   if ( this->getIfBackpackFull() ) {
//     err::raise<FullBackpackException>( "Backpack full. Cannot pick up." );
//   }
//   backpack_.push_back( artifact );
// }

// void Character::equipArtifact( ArtifactType type, EquipmentSlots slot ) {
//   std::optional<EquipmentSlots> slot_if_empty = this->checkSlotIfEmpty( slot );
//   EquipmentSlots slot_specific;
//   if ( !slot_if_empty.has_value() ) {
//     err::raise<NotEmptySlotException>( "Cannot equip into a full slot" );
//   }
//   slot_specific = slot_if_empty.value();

//   std::optional<Artifact> artifact_temp = std::nullopt;
//   for ( auto it = backpack_.begin(); it != backpack_.end(); ++it ) {
//     if ( it->getData().type_ != type ) {
//       continue;
//     }
//     if ( it->getData().slot_ != slot ) {
//       err::raise<InvalidSlotException>( "This artifact cannot be equipped into that slot" );
//     }
//     artifact_temp = it->copy();
//     backpack_.erase( it );
//     break;
//   }
//   if ( !artifact_temp ) {
//     err::raise<InvalidArtifactTypeException>( "No such artifact found in backpack" );
//   }
//   equipment_[slot_specific] = artifact_temp;
// }

// void Character::unequipArtifact( EquipmentSlots slot ) {
//   if ( this->getIfBackpackFull() ) {
//     err::raise<FullBackpackException>( "Backpack full. Cannot unequip." );
//   }
//   if ( !equipment_[slot] ) {
//     err::raise<EmptySlotException>( "This slot is empty. Cannot unequip." );
//   }
//   backpack_.push_back( *equipment_[slot] );
//   equipment_[slot] = std::nullopt;
// }

// void Character::recruitWarMachine( std::unique_ptr<const Ballista> war_machine ) {
//   if ( war_machines_["ballista"] != nullptr ) {
//     err::raise<NotEmptySlotException>( "This slot is not empty. Cannot recruit." );
//   }
//   war_machines_["ballista"] = std::move( war_machine );
// }
// void Character::recruitWarMachine( std::unique_ptr<const AmmoCart> war_machine ) {
//   if ( war_machines_["ammo_cart"] != nullptr ) {
//     err::raise<NotEmptySlotException>( "This slot is not empty. Cannot recruit." );
//   }
//   war_machines_["ammo_cart"] = std::move( war_machine );
// }
// void Character::recruitWarMachine( std::unique_ptr<const FirstAidTent> war_machine ) {
//   if ( war_machines_["first_aid_tent"] != nullptr ) {
//     err::raise<NotEmptySlotException>( "This slot is not empty. Cannot recruit." );
//   }
//   war_machines_["first_aid_tent"] = std::move( war_machine );
// }
// void Character::recruitWarMachine( std::unique_ptr<const Catapult> war_machine ) {
//   if ( war_machines_["catapult"] != nullptr ) {
//     err::raise<NotEmptySlotException>( "This slot is not empty. Cannot recruit." );
//   }
//   war_machines_["catapult"] = std::move( war_machine );
// }
// void Character::unequipWarMachine( const std::string& slot_name ) {
//   if ( war_machines_[slot_name] == nullptr ) {
//     err::raise<EmptySlotException>( "This slot is empty. Cannot unequip." );
//   }
//   // TODO empty slot, drop machine
// }

void Character::equipSpellBook( SpellBook spell_book ) {
  if ( !this->spell_book_ ) {
    err::raise<NotEmptySlotException>( "This slot is not empty. Cannot equip." );
  }
  this->spell_book_ = std::move( spell_book );
}
SpellBook Character::unequipSpellBook() {
  if ( !spell_book_ ) {
    err::raise<EmptySlotException>();
  }
  auto spell_book = std::move( this->spell_book_ );
  this->spell_book_ = std::nullopt;
  return std::move( *spell_book );
}

// const std::vector<Artifact>& Character::getBackpack() {
//   return this->backpack_;
// }
// std::array<std::shared_ptr<UnitStack>, MAX_PARTY_SIZE>& Character::getParty() {
//   return this->party_;
// }
// uint32_t Character::getPartySize() {
//   uint32_t party_count = 0;
//   for ( const auto& mp : this->party_ ) {
//     if ( mp != nullptr ) {
//       ++party_count;
//     }
//   }
//   return party_count;
// }

// void Character::recruitUnitStack( std::shared_ptr<UnitStack> unit_stack ) {
//   if ( getPartySize() == MAX_PARTY_SIZE ) {
//     err::raise<NotEmptySlotException>( "No empty slot in Party to recuit a new unit" );
//   }
//   for ( auto& mp : this->party_ ) {
//     if ( mp == nullptr ) {
//       mp = unit_stack;
//       return;
//     }
//   }
// }
std::shared_ptr<Character> Character::copy() {
  return nullptr;  // TODO fix
}
//   std::shared_ptr<Character> copy =
//       std::make_shared<Character>( this->name_, this->coords_, this->attack_, this->defense_, this->power_,
//                                    this->knowledge_, this->max_mana_, this->morale_, this->luck_ );
//   copy->alive_ = this->alive_;
//   copy->level_ = this->level_;
//   copy->experience_ = this->experience_;
//   copy->current_mana_ = this->current_mana_;
//   copy->movement_points_ = this->movement_points_;

//   for ( uint32_t i = 0; i < SECONDARY_SKILLS_SLOTS_COUNT; ++i ) {
//     if ( this->secondary_skills_[i] != nullptr ) {
//       copy->secondary_skills_[i] = secondary_skills_[i]->copy();
//     } else {
//       copy->secondary_skills_[i] = nullptr;
//     }
//   }

//   for ( const auto& [slot, artifact] : this->equipment_ ) {
//     if ( !artifact ) {
//       copy->equipment_[slot] = artifact->copy();
//     } else {
//       copy->equipment_[slot] = std::nullopt;
//     }
//   }

//   for ( const auto& [slot, war_machine] : this->war_machines_ ) {
//     if ( war_machine != nullptr ) {
//       copy->war_machines_[slot] = war_machine->copy();
//     } else {
//       copy->war_machines_[slot] = nullptr;
//     }
//   }

//   if ( this->spell_book_ != nullptr ) {
//     copy->spell_book_ = this->spell_book_->copy();
//   } else {
//     copy->spell_book_ = nullptr;
//   }

//   for ( const auto& artifact : this->backpack_ ) {
//     copy->backpack_.push_back( artifact.copy() );
//   }

//   for ( uint32_t i = 0; i < MAX_PARTY_SIZE; ++i ) {
//     if ( this->party_.at( i ) != nullptr ) {
//       copy->party_.at( i ) = this->party_.at( i )->copy();
//     } else {
//       copy->party_.at( i ) = nullptr;
//     }
//   }
//   return copy;
// }