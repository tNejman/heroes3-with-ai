#pragma once
// autor: Tomasz Nejman
/* zawarość klasa spell:
    - klasa ma pozwalać na rzucanie zaklęć
*/
#include <functional>

#include "core/Magic/SpellLib.h"

// NOLINTBEGIN(cppcoreguidelines-special-member-functions)
class Spell {
 private:
  std::reference_wrapper<spell::BaseData> data_;

  Spell( const spell::BaseData& data ) noexcept;

 public:
  virtual ~Spell() = default;
  [[nodiscard]] friend constexpr bool operator==( const Spell&, const Spell& ) noexcept = default;

  [[nodiscard]] const spell::BaseData& getData() const noexcept;
};
// NOLINTEND(cppcoreguidelines-special-member-functions)