#pragma once

// Autor: Tomasz Nejman
/* zawartość:
    - klasa 'AttackMove' to podklasa 'Move' i reprezetnuje ruch, w którym oddział jednostek atakuje inny oddział
*/

#include "Battle/Battle.h"
#include "Battle/Moves/Move.hpp"

class AttackMove : public Move {
 private:
  CoordPair attacker_;
  CoordPair defender_;

 public:
  AttackMove( CoordPair attacker, CoordPair defender);
  ~AttackMove();
  void execute(std::shared_ptr<Battle> battle) override;
  CoordPair destinationCoords() const override;
  std::string getPath() const override;
  std::string getInfo(std::shared_ptr<Battle> battle)const override;
  std::shared_ptr<Move> copy() const override;
};