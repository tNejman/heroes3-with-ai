#pragma once
// Autor: Tomasz Nejman
/* Zawartość klasy spellbook:
    - klasa pozwala na przechowywanie zaklęć
    - klasa pozwala na rzucanie zaklęć znajdujących się w spellbooku
*/
#include <vector>

#include "core/Magic/Spell.h"

// public Printable
class SpellBook {
 private:
  std::vector<Spell> spells_;

 public:
  SpellBook() = default;
  SpellBook( const SpellBook& ) = delete;
  SpellBook( SpellBook&& ) = default;
  ~SpellBook() = default;
  SpellBook& operator=( const SpellBook& ) = delete;
  SpellBook& operator=( SpellBook&& ) = default;

  friend class CharacterSaver;
  void learnSpell( Spell spell );
  [[nodiscard]] SpellBook copy() const;
};