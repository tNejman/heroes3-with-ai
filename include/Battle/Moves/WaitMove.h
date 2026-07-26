#pragma once

#include <memory>
#include <string>

#include "Battle/Battle.h"
#include "Battle/Moves/Move.hpp"
#include "Miscellaneous/Coords.h"


class WaitMove : public Move {
 private:
  CoordPair coords_;

 public:
  WaitMove( CoordPair coords );
  void execute( std::shared_ptr<Battle> battle ) override;
  [[nodiscard]] std::string getInfo( std::shared_ptr<Battle> battle ) const override;
  [[nodiscard]] CoordPair destinationCoords() const override;
  [[nodiscard]] std::string getPath() const override;
  [[nodiscard]] std::shared_ptr<Move> copy() const override;
};