#pragma once

// Autor: Tomasz Nejman
/* zawartość:
    - klasa 'AttackMove' to podklasa 'Move' i reprezetnuje ruch, w którym oddział jednostek atakuje inny oddział
*/

#include <memory>
#include <string>

#include "Battle/Battle.h"
#include "Battle/Moves/Move.hpp"
#include "Miscellaneous/Coords.h"


class AttackMove : public Move {
 private:
  CoordPair attacker_;
  CoordPair defender_;

 public:
  AttackMove( CoordPair attacker, CoordPair defender );
  void execute( std::shared_ptr<Battle> battle ) override;
  [[nodiscard]] CoordPair destinationCoords() const override;
  [[nodiscard]] std::string getPath() const override;
  [[nodiscard]] std::string getInfo( std::shared_ptr<Battle> battle ) const override;
  [[nodiscard]] std::shared_ptr<Move> copy() const override;
};