#include "core/Character/SecondarySkill.h"

#include <memory>

#include "engine/Graphics/Visitor.h"

constexpr SecondarySkill::SecondarySkill( SecondarySkill::Type skill_type ) noexcept
    : type_( skill_type ), level_( SecondarySkill::Level::BASIC ) {};

constexpr SecondarySkill::SecondarySkill( SecondarySkill::Type skill_type, SecondarySkill::Level skill_level ) noexcept
    : type_( skill_type ), level_( skill_level ) {};

SecondarySkill::Type SecondarySkill::getType() const {
  return this->type_;
}

SecondarySkill::Level SecondarySkill::getLevel() const {
  return this->level_;
}

std::unique_ptr<SecondarySkill> SecondarySkill::copy() const {
  // std::unique_ptr<SecondarySkill> copy = std::make_unique<SecondarySkill>( this->type_, this->level_ );
  // copy->cost_ = this->cost_;
  // return copy;
  return nullptr;  // TODO make actual copy
}