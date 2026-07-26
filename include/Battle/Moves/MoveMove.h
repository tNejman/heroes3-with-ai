#pragma once

// Autor: Tomasz Nejman
/* zawartość:
    - klasa 'AttackMove' to podklasa 'Move' i reprezetnuje ruch, w którym oddział jednostek przemieszcza się na nowe pole
*/

#include "Battle/Battle.h"
#include "Battle/Moves/Move.hpp"

class MoveMove : public Move {
 private:
  CoordPair old_coords_;
  CoordPair new_coords_;

 public:
  MoveMove( CoordPair old_coords, CoordPair new_coords );
  ~MoveMove();
  void execute(std::shared_ptr<Battle> battle) override;
  virtual CoordPair destinationCoords() const override;
  virtual std::string getPath() const override;
  std::string getInfo(std::shared_ptr<Battle> battle) const override;
  virtual std::shared_ptr<Move> copy() const override;
};