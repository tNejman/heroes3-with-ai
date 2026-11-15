#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy AIPlayer:
    -jest implementacją klasy AIPlayer
*/
#include "core/Battle/Battle.h"
#include "core/Player/Personalities/Personality.h"
#include "core/Player/Player.h"

class AIPlayer : public Player {
 private:
  int hardness_;
  std::shared_ptr<Personality> personality;

 public:
  [[nodiscard]] AIPlayer( int hardness, std::shared_ptr<Personality> personality ) noexcept
      : hardness_( hardness ), personality( personality ) {
  }
  [[nodiscard]] std::shared_ptr<Personality> getPersonality() const noexcept;
  void setPersonality( std::shared_ptr<Personality> personality ) noexcept;
  [[nodiscard]] int getHardness() const noexcept;
  void setHardness( int hardness ) noexcept;
  // std::shared_ptr<Move> MakeMove(std::vector<Move> PossibleStates) override;
};
