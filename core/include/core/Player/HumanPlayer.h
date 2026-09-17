#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Player:
    -jest implementacją klasy Player dla człowieka
*/
#include "core/Battle/Battle.h"
#include "core/Player/Player.h"
class HumanPlayer : public Player {
 private:
 public:
  HumanPlayer() = default;
  // std::shared_ptr<Move> MakeMove(std::vector<Move> PossibleStates) override;
};
