#include "Characters/SecondarySkill.h"

SecondarySkill::SecondarySkill( SecondarySkillType skill_type )
    : type_( skill_type ), level_( SecondarySkillLevel::BASIC ) {};

std::string SecondarySkill::getName() const {
  std::string name;
  switch ( this->type_ ) {
    case SecondarySkillType::AIR_MAGIC:
      return "Air Magic";
    case SecondarySkillType::FIRE_MAGIC:
      return "Fire Magic";
    case SecondarySkillType::EARTH_MAGIC:
      return "Earth Magic";
    case SecondarySkillType::WATER_MAGIC:
      return "Water Magic";
    default:
      return "";
  }
}

sf::Texture& SecondarySkill::accept( Visitor& v ) const {
  return v.visit( *this );
}

SecondarySkillType SecondarySkill::getType() const {
  return this->type_;
}

SecondarySkillLevel SecondarySkill::getLevel() const {
  return this->level_;
}

std::unique_ptr<SecondarySkill> SecondarySkill::copy() const {
  std::unique_ptr<SecondarySkill> copy =
      std::make_unique<SecondarySkill>( this->type_ );
  copy->level_ = this->level_;
  copy->cost_ = this->cost_;
  return copy;
  // switch ( this->type_ ) {
  //   case SecondarySkillType::AIR_MAGIC:
  //     return std::make_unique<AirMagic>();
  //   case SecondarySkillType::FIRE_MAGIC:
  //     return std::make_unique<FireMagic>();
  //   case SecondarySkillType::EARTH_MAGIC:
  //     return std::make_unique<EarthMagic>();
  //   case SecondarySkillType::WATER_MAGIC:
  //     return std::make_unique<WaterMagic>();
  //   default:
  //     throw BadCopyException( "Cannot copy SecondarySkill of unknown type." );
  // }
}