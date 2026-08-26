#pragma once

#include <memory>
#include <vector>

#include "WorldMap/Castles/CastleInterface.h"

class Castle : public CastleInterface {
 private:
  std::weak_ptr<Character> garnisoned_character_;
  std::weak_ptr<Character> standing_chacter_;
  std::vector<std::weak_ptr<Building>> built_buildings_;

 public:
};