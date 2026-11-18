#pragma once
// Autor: Tomasz Nejman

#include <string>

#include "engine/model/IGame/Coords.h"

#include "core/MapObject/MapObject.h"

/**
 * @note don't derive visitor::Visitable here, Building is not final child
 */
class Building : public MapObject {
 private:
  std::string name_;

 public:
  [[nodiscard]] Building( CoordPair coords, std::string name ) noexcept;

  [[nodiscard]] std::string getName() const;
};