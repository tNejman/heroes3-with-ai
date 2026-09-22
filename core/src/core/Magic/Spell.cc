#include "core/Magic/Spell.h"

[[nodiscard]] const spell::BaseData& Spell::getData() const noexcept {
  return data_.get();
}