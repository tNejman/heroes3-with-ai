#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy AIPlayer:
    -jest implementacją klasy AIPlayer
*/
#include "Battle/Battle.h"
#include "Player/Personalities/Personality.h"
#include "Player/Player.h"

class AIPlayer : public Player {
 private:
  int hardness_;
  std::shared_ptr<Personality> personality;

 public:
  AIPlayer( int hardness, std::shared_ptr<Personality> personality )
      : hardness_( hardness ), personality( personality ) {}
  std::shared_ptr<Personality> getPersonality() const;
  void setPersonality( std::shared_ptr<Personality> personality );
  int getHardness() const;
  void setHardness( int hardness );
  // std::shared_ptr<Move> MakeMove(std::vector<Move> PossibleStates) override;
};
