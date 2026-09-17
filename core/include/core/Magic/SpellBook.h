#pragma once
// Autor: Tomasz Nejman
/* Zawartość klasy spellbook:
    - klasa pozwala na przechowywanie zaklęć
    - klasa pozwala na rzucanie zaklęć znajdujących się w spellbooku
*/
#include <memory>
#include <vector>

#include "core/Magic/Spell.h"
#include "core/Misc/Equippable.h"

// public Printable
class SpellBook : public Equippable {
 private:
  std::vector<std::unique_ptr<Spell>> spells_;

 public:
  friend class CharacterSaver;
  void learnSpell( std::unique_ptr<Spell> spell );
  [[nodiscard]] std::unique_ptr<SpellBook> copy() const;
};