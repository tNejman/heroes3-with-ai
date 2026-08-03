#pragma once

namespace {
constexpr inline int DEFAULT_CHARACTER_PS_ATTACK = 10;
constexpr inline int DEFAULT_CHARACTER_PS_DEFENSE = 10;
constexpr inline int DEFAULT_CHARACTER_PS_POWER = 10;
constexpr inline int DEFAULT_CHARACTER_PS_KNOWLEDGE = 10;

constexpr inline int DEFAULT_CHARACTER_LEVEL = 1;
constexpr inline int DEFAULT_CHARACTER_EXPERIENCE = 0;

constexpr inline int DEFAULT_CHARACTER_MAX_MANA = 0;

constexpr inline int DEFAULT_CHARACTER_MORALE = 0;
constexpr inline int DEFAULT_CHARACTER_LUCK = 0;

constexpr inline int DEFAULT_MAX_MOVEMENT_POINTS = 10;
}  // namespace

class CharacterStats {
 public:
  struct PrimarySkills {
    int attack_ = DEFAULT_CHARACTER_PS_ATTACK;
    int defense_ = DEFAULT_CHARACTER_PS_DEFENSE;
    int power_ = DEFAULT_CHARACTER_PS_POWER;
    int knowledge_ = DEFAULT_CHARACTER_PS_KNOWLEDGE;
  };
  struct Level {
    int level_ = DEFAULT_CHARACTER_LEVEL;
    int experience_ = DEFAULT_CHARACTER_EXPERIENCE;
  };
  struct Mana {
    int max_mana_ = DEFAULT_CHARACTER_MAX_MANA;
    int current_mana_ = max_mana_;
  };
  struct Misc {
    int morale_ = DEFAULT_CHARACTER_MORALE;
    int luck_ = DEFAULT_CHARACTER_LUCK;
  };
  struct Movement {
    int max_movement_points_ = DEFAULT_MAX_MOVEMENT_POINTS;
    int current_movement_points_ = max_movement_points_;
  };
  //   std::vector<StatModifier> aux_modifiers_; @TODO

 private:
  PrimarySkills primary_skills_;
  Level level_;
  Mana mana_;
  Misc misc_;
  Movement movement_;

 public:
  CharacterStats();
  CharacterStats( PrimarySkills primary_skills );
  CharacterStats( Misc misc );
  CharacterStats( PrimarySkills primary_skills, Misc misc );
  CharacterStats( const CharacterStats& ) = delete;
  CharacterStats( CharacterStats&& ) = default;
  ~CharacterStats() = default;
  CharacterStats& operator=( const CharacterStats& ) = delete;
  CharacterStats& operator=( CharacterStats&& ) = default;

  [[nodiscard]] const PrimarySkills& getPrimarySkills() const noexcept;
  [[nodiscard]] const Level& getLevel() const noexcept;
  [[nodiscard]] const Mana& getMana() const noexcept;
  [[nodiscard]] const Misc& getMisc() const noexcept;
  [[nodiscard]] const Movement& getMovement() const noexcept;

  //   [[nodiscard]] uint32_t getAttack() const;
  //   void setAttack( const uint32_t new_attack );
  //   void modifyAttack( const uint32_t attack_diff );

  //   [[nodiscard]] uint32_t getDefense() const;
  //   void setDefense( const uint32_t new_defense );
  //   void modifyDefense( const uint32_t defense_diff );

  //   [[nodiscard]] uint32_t getPower() const;
  //   void setPower( const uint32_t new_power );
  //   void modifyPower( const uint32_t power_diff );

  //   [[nodiscard]] uint32_t getKnowledge() const;
  //   void setKnowledge( const uint32_t new_knowledge );
  //   void modifyKnowledge( const uint32_t knowledge_diff );

  //   [[nodiscard]] uint32_t getMovementPoints() const;
  //   void setMovementPoints( const uint32_t new_movement );
  //   void modifyMovementPoints( const uint32_t movement_diff );

  //   [[nodiscard]] uint32_t getLevel() const;
  //   [[nodiscard]] uint32_t getExperience() const;
  //   void gainExperience( const uint32_t experience );

  //   [[nodiscard]] uint32_t getMaxMana() const;
  //   void setMaxMana( const uint32_t new_max_mana );
  //   void modifyMaxMana( const uint32_t max_mana_diff );

  //   [[nodiscard]] uint32_t getCurrentMana() const;
  //   void setCurrentMana( const uint32_t new_current_mana );
  //   void modifyCurrentMana( const uint32_t current_mana_diff );

  //   [[nodiscard]] int getMorale() const;
  //   void setMorale( const int new_morale );
  //   void modifyMorale( const int morale_diff );

  //   [[nodiscard]] int getLuck() const;
  //   void setLuck( const int new_luck );
  //   void modifyLuck( const int luck_diff );
};