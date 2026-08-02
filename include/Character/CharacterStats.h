#pragma once

class CharacterStats {
 public:
  struct PrimarySkills {
    int attack_;
    int defense_;
    int power_;
    int knowledge_;
  };
  struct Level {
    int level_;
    int experience_;
  };
  struct Mana {
    int max_mana_;
    int current_mana_;
  };
  struct Misc {
    int morale_;
    int luck_;
  };
  //   std::vector<StatModifier> aux_modifiers_; @TODO

 private:
  PrimarySkills primary_skills_;
  Level level_;
  Mana mana_;
  Misc misc_;

 public:
  CharacterStats() = delete;
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