#pragma once
// Autor: Tomasz Nejman
/* Zawartość klasy spellbook:
    - klasa pozwala na przechowywanie zaklęć
    - klasa pozwala na rzucanie zaklęć znajdujących się w spellbooku
*/
#include <memory>
#include <vector>

#include "Magic/Spell.h"
#include "Miscellaneous/Equippable.h"
#include "Miscellaneous/Printable.h"

// public Printable
class SpellBook : public Equippable {
 private:
  std::vector<std::unique_ptr<Spell>> spells_;

 public:
  friend class CharacterSaver;
  SpellBook();
  ~SpellBook();
  //  virtual sf::Texture& accept(Visitor& v) const override { return v.visit(*this); }
  void learnSpell( std::unique_ptr<Spell> spell );
  std::unique_ptr<SpellBook> copy() const;
};