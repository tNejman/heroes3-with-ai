#include "Character/CharacterStats.h"

// uint32_t Character::getAttack() const {
//   return this->attack_;
// }

// void Character::setAttack( const uint32_t new_attack ) {
//   this->attack_ = new_attack;
// }

// void Character::modifyAttack( const uint32_t attack_diff ) {
//   this->attack_ += attack_diff;
// }

// uint32_t Character::getDefense() const {
//   return this->defense_;
// }

// void Character::setDefense( const uint32_t new_defense ) {
//   this->defense_ = new_defense;
// }

// void Character::modifyDefense( const uint32_t defense_diff ) {
//   this->defense_ += defense_diff;
// }

// uint32_t Character::getPower() const {
//   return this->power_;
// }

// void Character::setPower( const uint32_t new_power ) {
//   this->power_ = new_power;
// }

// void Character::modifyPower( const uint32_t power_diff ) {
//   this->power_ += power_diff;
// }

// uint32_t Character::getKnowledge() const {
//   return this->knowledge_;
// }

// void Character::setKnowledge( const uint32_t new_knowledge ) {
//   this->knowledge_ = new_knowledge;
// }

// void Character::modifyKnowledge( const uint32_t knowledge_diff ) {
//   this->knowledge_ += knowledge_diff;
// }

// uint32_t Character::getMovementPoints() const {
//   return movement_points_;
// }

// void Character::setMovementPoints( const uint32_t new_movement ) {
//   this->movement_points_ = new_movement;
// }

// void Character::modifyMovementPoints( const uint32_t movement_diff ) {
//   this->movement_points_ += movement_diff;
// }

// uint32_t Character::getLevel() const {
//   return this->level_;
// }

// uint32_t Character::getExperience() const {
//   return this->experience_;
// }

// void Character::gainExperience( const uint32_t experience ) {
//   uint32_t old_level = this->level_;

//   this->experience_ += experience;

//   if ( this->experience_ >= static_cast<uint32_t>( EXPERIENCE_THRESHHOLDS.at( old_level + 1 ) ) ) {
//     ++level_;
//   }
// }

// uint32_t Character::getMaxMana() const {
//   return this->max_mana_;
// }
// void Character::setMaxMana( const uint32_t new_max_mana ) {
//   this->max_mana_ = new_max_mana;
// }
// void Character::modifyMaxMana( const uint32_t max_mana_diff ) {
//   this->max_mana_ += max_mana_diff;
// }

// uint32_t Character::getCurrentMana() const {
//   return this->current_mana_;
// }
// void Character::setCurrentMana( const uint32_t new_current_mana ) {
//   this->current_mana_ = new_current_mana;
// }
// void Character::modifyCurrentMana( const uint32_t current_mana_diff ) {
//   this->current_mana_ += current_mana_diff;
// }

// int Character::getMorale() const {
//   return this->morale_;
// }
// void Character::setMorale( const int new_morale ) {
//   this->morale_ = new_morale;
// }
// void Character::modifyMorale( const int morale_diff ) {
//   this->morale_ += morale_diff;
// }

// int Character::getLuck() const {
//   return this->luck_;
// }
// void Character::setLuck( const int new_luck ) {
//   this->luck_ = new_luck;
// }
// void Character::modifyLuck( const int luck_diff ) {
//   this->luck_ += luck_diff;
// }