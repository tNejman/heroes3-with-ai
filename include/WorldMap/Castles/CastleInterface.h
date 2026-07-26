#pragma once

#include <array>
#include <memory>
#include <vector>

// #include "Characters/Character.h"
// #include "WorldMap/Building.h"
#include "WorldMap/MapObject.h"

class Character;
class Building;

class CastleInterface : public MapObject {
 private:
  std::vector<std::weak_ptr<Building>> available_buildings;

 public:
};