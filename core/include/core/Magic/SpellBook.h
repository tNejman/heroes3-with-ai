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
  [[nodiscard]] constexpr SpellBook() noexcept = default;
  SpellBook( const SpellBook& ) = delete;
  [[nodiscard]] constexpr SpellBook( SpellBook&& ) noexcept = default;
  ~SpellBook() noexcept = default;
  SpellBook& operator=( const SpellBook& ) = delete;
  SpellBook& operator=( SpellBook&& ) noexcept = default;

  friend class CharacterSaver;
  void learnSpell( Spell spell ) noexcept;
  [[nodiscard]] SpellBook copy() const noexcept;
};