#pragma once
// Autor: Tomasz Nejman

#include <string>

#include "core/MapObject/MapObject.h"
#include "engine/model/IGame/Coords.h"

/**
 * @note don't derive visitor::Visitable here, Building is not final child
 */
class Building : public MapObject {
 private:
  std::string name_;

 public:
  Building( CoordPair coords, std::string name );

  [[nodiscard]] std::string getName() const;
};