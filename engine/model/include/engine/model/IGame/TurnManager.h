#pragma once

#include <memory>
#include <vector>

#include "engine/model/IGame/ITurnEffect.hpp"

// @TODO introduce events and make a one generic list, with triggers and subscribers etc.

enum class TurnEffectType : bool { END_OF_TURN, BEGINNING_OF_TURN };

class TurnManager {
 private:
  std::vector<std::unique_ptr<ITurnEffect>> end_of_turn_effects_;
  std::vector<std::unique_ptr<ITurnEffect>> beggining_of_turn_effects_;

  static void removeExpiredEffects( std::vector<std::unique_ptr<ITurnEffect>>& ) noexcept;
  static void updateEffectDuration( ITurnEffect& ) noexcept;
  static void performEffects( std::vector<std::unique_ptr<ITurnEffect>>& ) noexcept;

 public:
  void performEffects( TurnEffectType ) noexcept;
};