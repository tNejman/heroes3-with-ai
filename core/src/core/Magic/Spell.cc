#include "core/Magic/Spell.h"

#include <cstddef>

#include "core/Magic/SpellLib.h"

/* ==== @PRIVATE ==== */

Spell::Spell( const spell::BaseData& data ) noexcept : data_( data ) {
}

/* ==== @PUBLIC =====*/

[[nodiscard]] Spell Spell::create( spell::Type type ) noexcept {
  return Spell{ spell::BASE_PRESET[static_cast<size_t>( type )] };
}

[[nodiscard]] const spell::BaseData& Spell::getData() const noexcept {
  return data_.get();
}