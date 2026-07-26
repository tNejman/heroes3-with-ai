#pragma once
// #include <SFML/Graphics.hpp>

#include <array>
#include <memory>
#include <vector>

#include "Miscellaneous/Printable.h"
#include "WorldMap/Castles/CastleInterface.h"

// inheritance from Printable is postponed for now
class Castle : public CastleInterface {
 private:
  std::weak_ptr<Character> garnisoned_character_;
  std::weak_ptr<Character> standing_chacter_;
  std::vector<std::weak_ptr<Building>> built_buildings;

 public:
  // virtual sf::Texture& accept(Visitor& v) const override {v.visit(*this);}
};