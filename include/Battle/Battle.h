#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy battle:
  - Klasa Battle odpowiada za zarządzanie bitwą pomiędzy dwoma armiami.
  - Zawiera metody do atakowania jednostek, zarządzania kolejnością jednostek w bitwie.
*/
#include <stdint.h>

#include <array>
#include <cassert>
#include <memory>
#include <queue>
#include <set>
#include <vector>

#include "Battle/BattleField.h"
#include "Battle/Obstacle.h"
#include "Battle/Tile.h"
#include "Battle/TileObject.h"
// #include "Battle/Moves/MoveFactory.h"
#include "Characters/Character.h"
#include "Miscellaneous/Printable.h"
#include "WorldMap/GridTile.h"
class MoveFactory;
class Move;

class Battle : public Printable, std::enable_shared_from_this<Battle> {
 private:
  BattleState state_ = BattleState::PREPPING;
  std::shared_ptr<BattleField> battlefield_;
  std::shared_ptr<Character> attacker_;
  std::shared_ptr<Character> defender_;
  size_t round_counter_ = 0;
  bool attacker_threw_spell_;
  bool defender_threw_spell_;
  // std::vector<std::shared_ptr<UnitStack>> attacking_army_;
  // std::vector<std::shared_ptr<UnitStack>> defending_army_;
  // std::vector<std::shared_ptr<UnitStack>> units_in_battle_;
  std::vector<std::shared_ptr<UnitStack>> round_queue_;
  void setAttackingArmy();
  void setDefendingArmy();
  uint32_t setUnitInQueue( std::shared_ptr<UnitStack> unit );
  void createObstacles();
  void nextRound();
  std::shared_ptr<UnitStack> unit_in_action_;
  std::vector<std::shared_ptr<Move>> possible_moves_;

  bool is_minimax_ = false;

 public:
  friend MoveFactory;
  Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, std::shared_ptr<GridTile> background );
  Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, std::shared_ptr<GridTile> background, bool is_minimax );

  ~Battle() noexcept override = default;
  sf::Texture& accept( Visitor& v ) const override;
  BattleState getState() const;
  bool setUnit( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords );
  bool killUnit( std::shared_ptr<UnitStack> dead_unit_to_kill );
  void setBattleState( BattleState state );
  bool move( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords );
  bool attack( std::shared_ptr<UnitStack> attacker, std::shared_ptr<UnitStack> defender );
  std::shared_ptr<BattleField> getBattlefield();
  std::shared_ptr<Character> getAttacker() const;
  std::shared_ptr<Character> getDefender() const;
  size_t getRoundCounter() const;
  std::shared_ptr<UnitStack> getUnitFromCoords( CoordPair coords ) const;
  bool hasAttackerThrownSpell() const;
  bool hasDefenderThrownSpell() const;
  void nextUnit();
  std::vector<std::shared_ptr<UnitStack>> getAttackingArmy() const;
  std::vector<std::shared_ptr<UnitStack>> getDefendingArmy() const;
  std::vector<std::shared_ptr<UnitStack>> getUnitsInBattle() const;
  std::vector<std::shared_ptr<UnitStack>> getUnitsInBattleSortedToPrint() const;
  std::vector<std::shared_ptr<UnitStack>> getRoundQueue() const;
  std::shared_ptr<UnitStack> getUnitInAction() const;
  std::vector<std::shared_ptr<Move>> getPossibleMoves() const;
  BattleState getBattleState() const;
  bool isSameArmy( const std::shared_ptr<UnitStack> unit1, const std::shared_ptr<UnitStack> unit2 ) const;
  bool isAIMove() const;
  void forceUnplaceUnitStacks();
  void forcePlaceUnitStack( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords );
  std::shared_ptr<Battle> copy();
};