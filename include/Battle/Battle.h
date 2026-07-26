#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy battle:
  - Klasa Battle odpowiada za zarządzanie bitwą pomiędzy dwoma armiami.
  - Zawiera metody do atakowania jednostek, zarządzania kolejnością jednostek w bitwie.
*/
#include <SFML/Graphics/Texture.hpp>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "Battle/BattleField.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/Printable.h"

class MoveFactory;
class Move;
class Character;
class UnitStack;
class GridTile;
class Visitor;

enum class BattleState {
  PREPPING,  //@Warning remove later possibly
  //   DEFENDING,
  MOVING,
  ATTACKING,
  //   CASTING_SPELL,
  //   SELECTING_TARGET
  WIN_ATTACKER,
  WIN_DEFENDER
};

class Battle : public Printable, std::enable_shared_from_this<Battle> {
 private:
  BattleState state_ = BattleState::PREPPING;
  std::shared_ptr<BattleField> battlefield_;
  std::shared_ptr<Character> attacker_;
  std::shared_ptr<Character> defender_;
  std::size_t round_counter_ = 0;
  bool attacker_threw_spell_;
  bool defender_threw_spell_;
  // std::vector<std::shared_ptr<UnitStack>> attacking_army_;
  // std::vector<std::shared_ptr<UnitStack>> defending_army_;
  // std::vector<std::shared_ptr<UnitStack>> units_in_battle_;
  std::vector<std::shared_ptr<UnitStack>> round_queue_;

  void setAttackingArmy();
  void setDefendingArmy();
  [[nodiscard]] uint32_t setUnitInQueue( std::shared_ptr<UnitStack> unit );
  void createObstacles();
  void nextRound();
  std::shared_ptr<UnitStack> unit_in_action_;
  std::vector<std::shared_ptr<Move>> possible_moves_;

  bool is_minimax_ = false;

 public:
  friend MoveFactory;
  Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
          std::shared_ptr<GridTile> background );
  Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
          std::shared_ptr<GridTile> background, bool is_minimax );

  [[nodiscard]] sf::Texture& accept( Visitor& vis ) const override;
  [[nodiscard]] BattleState getState() const;
  [[nodiscard]] bool setUnit( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords );
  [[nodiscard]] bool killUnit( std::shared_ptr<UnitStack> dead_unit_to_kill );
  void setBattleState( BattleState state );
  [[nodiscard]] bool move( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords );
  [[nodiscard]] bool attack( std::shared_ptr<UnitStack> attacker, std::shared_ptr<UnitStack> defender );
  [[nodiscard]] std::shared_ptr<BattleField> getBattlefield();
  [[nodiscard]] std::shared_ptr<Character> getAttacker() const;
  [[nodiscard]] std::shared_ptr<Character> getDefender() const;
  [[nodiscard]] size_t getRoundCounter() const;
  [[nodiscard]] std::shared_ptr<UnitStack> getUnitFromCoords( CoordPair coords ) const;
  [[nodiscard]] bool hasAttackerThrownSpell() const;
  [[nodiscard]] bool hasDefenderThrownSpell() const;
  void nextUnit();
  [[nodiscard]] std::vector<std::shared_ptr<UnitStack>> getAttackingArmy() const;
  [[nodiscard]] std::vector<std::shared_ptr<UnitStack>> getDefendingArmy() const;
  [[nodiscard]] std::vector<std::shared_ptr<UnitStack>> getUnitsInBattle() const;
  [[nodiscard]] std::vector<std::shared_ptr<UnitStack>> getUnitsInBattleSortedToPrint() const;
  [[nodiscard]] std::vector<std::shared_ptr<UnitStack>> getRoundQueue() const;
  [[nodiscard]] std::shared_ptr<UnitStack> getUnitInAction() const;
  [[nodiscard]] std::vector<std::shared_ptr<Move>> getPossibleMoves() const;
  [[nodiscard]] BattleState getBattleState() const;
  [[nodiscard]] bool isSameArmy( const std::shared_ptr<UnitStack> unit1, const std::shared_ptr<UnitStack> unit2 ) const;
  [[nodiscard]] bool isAIMove() const;
  void forceUnplaceUnitStacks();
  void forcePlaceUnitStack( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords );
  [[nodiscard]] std::shared_ptr<Battle> copy();
};