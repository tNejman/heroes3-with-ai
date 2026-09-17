#pragma once

#include <array>
#include <memory>
#include <vector>

// #include "core/Characters/Character.h"
// #include "core/WorldMap/Building.h"
#include "core/MapObject/MapObject.h"

class Character;
class Building;

class CastleInterface : public MapObject {
 private:
  std::vector<std::weak_ptr<Building>> available_buildings;

 public:
};