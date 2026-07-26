#pragma once

#include "Battle/Battle.h"
#include "Battle/Moves/Move.hpp"

class WaitMove : public Move {
 private:
  CoordPair coords_;

 public:
  WaitMove( CoordPair coords );

  ~WaitMove() override = default;
  void execute( std::shared_ptr<Battle> battle ) override;
  std::string getInfo( std::shared_ptr<Battle> battle ) const override;
  CoordPair destinationCoords() const override;
  std::string getPath() const override;
  std::shared_ptr<Move> copy() const override;
};