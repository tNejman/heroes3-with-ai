#pragma once

namespace character {

class Stats {
 private:
  static constexpr int DEFAULT_CHARACTER_PS_ATTACK = 10;
  static constexpr int DEFAULT_CHARACTER_PS_DEFENSE = 10;
  static constexpr int DEFAULT_CHARACTER_PS_POWER = 10;
  static constexpr int DEFAULT_CHARACTER_PS_KNOWLEDGE = 10;

  static constexpr int DEFAULT_CHARACTER_LEVEL = 1;
  static constexpr int DEFAULT_CHARACTER_EXPERIENCE = 0;

  static constexpr int DEFAULT_CHARACTER_MAX_MANA = 0;

  static constexpr int DEFAULT_CHARACTER_MORALE = 0;
  static constexpr int DEFAULT_CHARACTER_LUCK = 0;

  static constexpr int DEFAULT_MAX_MOVEMENT_POINTS = 10;

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
  constexpr Stats() noexcept = default;
  constexpr Stats( PrimarySkills, Level, Mana, Misc, Movement ) noexcept;

  [[nodiscard]] const PrimarySkills& getPrimarySkills() const noexcept;
  [[nodiscard]] const Level& getLevel() const noexcept;
  [[nodiscard]] const Mana& getMana() const noexcept;
  void spendMana( int amount ) noexcept;
  [[nodiscard]] const Misc& getMisc() const noexcept;
  [[nodiscard]] const Movement& getMovement() const noexcept;
};

}  // namespace character

/* ==== @IMPL ==== */
// obviously constexpr in header

constexpr character::Stats::Stats( PrimarySkills primary_skills, Level level, Mana mana, Misc misc,
                                   Movement movement ) noexcept
    : primary_skills_( primary_skills ), level_( level ), mana_( mana ), misc_( misc ), movement_( movement ) {
}