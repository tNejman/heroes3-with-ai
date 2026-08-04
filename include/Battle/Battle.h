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
#include <functional>
#include <memory>
#include <optional>
#include <vector>

#include "Battle/BattleField.h"
#include "Battle/TileObject.hpp"
#include "Graphics/Printable.h"
#include "Miscellaneous/Coords.h"
#include "Unit/UnitStack.h"
#include "Unit/UnitsLib.h"

class MoveFactory;
class Move;
class Character;
class UnitStack;
class GridTile;
class Visitor;

enum class BattleState : uint8_t {
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
  int round_counter_ = 0;
  bool attacker_threw_spell_;
  bool defender_threw_spell_;

  std::vector<std::reference_wrapper<UnitStack>> round_queue_;

  void setAttackingArmy();
  void setDefendingArmy();
  int setUnitInQueue( UnitStack& unit );
  void createObstacles();
  void nextRound();
  UnitStack* unit_in_action_ = nullptr;
  std::vector<std::shared_ptr<Move>> possible_moves_;

  bool is_minimax_ = false;

 public:
  friend MoveFactory;
  Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
          std::shared_ptr<GridTile> background );
  Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
          std::shared_ptr<GridTile> background, bool is_minimax );
  Battle( const Battle& ) = delete;
  Battle( Battle&& ) = delete;

  [[nodiscard]] sf::Texture& accept( Visitor& vis ) const override;
  [[nodiscard]] BattleState getState() const;
  [[nodiscard]] bool setUnit( UnitStack& unit_stack, CoordPair new_coords );
  [[nodiscard]] bool killUnit( UnitStack& dead_unit_to_kill );
  void setBattleState( BattleState state );
  bool move( UnitStack& unit_stack, CoordPair new_coords );
  bool attack( UnitStack& attacker, UnitStack& defender );
  [[nodiscard]] std::shared_ptr<BattleField> getBattlefield();
  [[nodiscard]] std::shared_ptr<Character> getAttacker() const;
  [[nodiscard]] std::shared_ptr<Character> getDefender() const;
  [[nodiscard]] int getRoundCounter() const;
  [[nodiscard]] UnitStack* getUnitFromCoords( CoordPair coords ) const;
  [[nodiscard]] bool hasAttackerThrownSpell() const;
  [[nodiscard]] bool hasDefenderThrownSpell() const;
  void nextUnit();
  [[nodiscard]] std::vector<std::reference_wrapper<UnitStack>> getAttackingArmy() const;
  [[nodiscard]] std::vector<std::reference_wrapper<UnitStack>> getDefendingArmy() const;
  [[nodiscard]] std::vector<std::reference_wrapper<UnitStack>> getUnitsInBattle() const;
  [[nodiscard]] std::vector<std::reference_wrapper<UnitStack>> getUnitsInBattleSortedToPrint() const;
  // [[nodiscard]] const std::vector<std::reference_wrapper<UnitStack>> getRoundQueue() const;
  [[nodiscard]] UnitStack* getUnitInAction() const;
  [[nodiscard]] std::vector<std::shared_ptr<Move>> getPossibleMoves() const;
  [[nodiscard]] BattleState getBattleState() const;
  [[nodiscard]] bool isSameArmy( const UnitStack& unit1, const UnitStack& unit2 ) const;
  [[nodiscard]] bool isAIMove() const;
  void forceUnplaceUnitStacks();
  void forcePlaceUnitStack( UnitStack& unit_stack, CoordPair new_coords );
  [[nodiscard]] std::shared_ptr<Battle> copy();
};