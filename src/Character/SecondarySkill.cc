#include "Character/SecondarySkill.h"

#include <memory>

#include "Graphics/Visitor.h"

SecondarySkill::SecondarySkill( SecondarySkillType skill_type )
    : type_( skill_type ), level_( SecondarySkillLevel::BASIC ), cost_( 0 ) {};

SecondarySkill::SecondarySkill( SecondarySkillType skill_type, SecondarySkillLevel skill_level )
    : type_( skill_type ), level_( skill_level ), cost_( 0 ) {};

void SecondarySkill::accept( Visitor& v ) const {
  v.visit( *this );
}

SecondarySkillType SecondarySkill::getType() const {
  return this->type_;
}

SecondarySkillLevel SecondarySkill::getLevel() const {
  return this->level_;
}

std::unique_ptr<SecondarySkill> SecondarySkill::copy() const {
  // std::unique_ptr<SecondarySkill> copy = std::make_unique<SecondarySkill>( this->type_, this->level_ );
  // copy->cost_ = this->cost_;
  // return copy;
  return nullptr;  // TODO make actual copy
}