#pragma once

// Autor: Tomasz Nejman
/* zawartość:
    - klasa 'AttackMove' to podklasa 'Move' i reprezetnuje ruch, w którym oddział jednostek przemieszcza się na nowe
   pole
*/

#include <memory>
#include <string>

#include "Battle/Moves/Move.hpp"
#include "Miscellaneous/Coords.h"

class MoveMove : public Move {
 private:
  CoordPair old_coords_;
  CoordPair new_coords_;

 public:
  MoveMove( CoordPair old_coords, CoordPair new_coords );
  void execute( std::shared_ptr<Battle> battle ) override;
  [[nodiscard]] CoordPair destinationCoords() const override;
  [[nodiscard]] std::string getPath() const override;
  [[nodiscard]] std::string getInfo( std::shared_ptr<Battle> battle ) const override;
  [[nodiscard]] std::shared_ptr<Move> copy() const override;
};