#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy battle:
  - Klasa Battle odpowiada za zarządzanie bitwą pomiędzy dwoma armiami.
  - Zawiera metody do atakowania jednostek, zarządzania kolejnością jednostek w bitwie.
*/
#include <cassert>
#include <cstdlib>
#include <functional>
#include <memory>
#include <vector>

#include "core/Battle/BattleField.h"
#include "core/Battle/TileObject.hpp"
#include "core/Game/UserCommand.h"
#include "core/Misc/ProjectLib.h"
#include "core/Unit/UnitStack.h"
#include "engine/model/IGame/Coords.h"

class MoveFactory;
class Character;
class UnitStack;
class GridTile;
class Visitor;

namespace battle {

enum class State : char {
  PREPPING,  //@Warning remove later possibly
  //   DEFENDING,
  MOVING,
  ATTACKING,
  //   CASTING_SPELL,
  //   SELECTING_TARGET
  WIN_ATTACKER,
  WIN_DEFENDER
};

};

class Battle : public std::enable_shared_from_this<Battle> {
 private:
  battle::State state_ = battle::State::PREPPING;
  std::shared_ptr<BattleField> battlefield_;
  std::shared_ptr<Character> attacker_;
  std::shared_ptr<Character> defender_;
  Character* current_character_;
  int round_counter_ = 0;
  bool has_attacker_thrown_spell_this_turn_ = false;
  bool has_defender_thrown_spell_this_turn_ = false;
  std::function<int( void )> randint_ = std::rand;  // @TODO mock

  std::vector<std::reference_wrapper<UnitStack>> round_queue_;

  void setAttackingArmy();
  void setDefendingArmy();
  int setUnitInQueue( UnitStack& unit );
  void createObstacles();
  void nextRound();
  UnitStack* unit_in_action_ = nullptr;
  std::vector<UserCommand> possible_moves_;

  bool is_minimax_ = false;

 public:
  friend MoveFactory;
  Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, Terrain background );
  Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, Terrain background,
          bool is_minimax );
  Battle( const Battle& ) = delete;
  Battle( Battle&& ) = delete;
  Battle& operator=( const Battle& ) = delete;
  Battle& operator=( Battle&& ) = delete;
  ~Battle() = default;

  [[nodiscard]] battle::State getState() const;
  [[nodiscard]] bool setUnit( UnitStack& unit_stack, CoordPair new_coords );
  bool killUnit( UnitStack& dead_unit_to_kill );
  void setBattleState( battle::State state );
  bool move( UnitStack& unit_stack, CoordPair new_coords );
  bool attack( UnitStack& attacking_unit, UnitStack& defending_unit );

  [[nodiscard]] bool isUnitBlocked( const UnitStack& ) const noexcept;

  [[nodiscard]] std::shared_ptr<BattleField> getBattlefield() const noexcept;
  [[nodiscard]] std::shared_ptr<BattleField> getBattlefield() noexcept;
  [[nodiscard]] std::shared_ptr<Character> getAttacker() const;
  [[nodiscard]] std::shared_ptr<Character> getDefender() const;
  [[nodiscard]] int getRoundCounter() const;
  [[nodiscard]] const UnitStack* getUnitFromCoords( CoordPair coords ) const noexcept;
  [[nodiscard]] UnitStack* getUnitFromCoords( CoordPair coords ) noexcept;
  [[nodiscard]] bool hasCurrentCharacterThrownSpell() const noexcept;
  void setCurrentCharacterThrownSpellTrue() noexcept;
  void nextUnit();
  [[nodiscard]] std::vector<std::reference_wrapper<UnitStack>> getAttackingArmy() const noexcept;
  [[nodiscard]] std::vector<std::reference_wrapper<UnitStack>> getDefendingArmy() const noexcept;
  [[nodiscard]] std::vector<std::reference_wrapper<UnitStack>> getUnitsInBattle() const noexcept;
  [[nodiscard]] std::vector<std::reference_wrapper<UnitStack>> getCurrentCharacterArmy() const noexcept;
  [[nodiscard]] std::vector<std::reference_wrapper<UnitStack>> getOpposingCharacterArmy() const noexcept;
  [[nodiscard]] std::vector<std::reference_wrapper<UnitStack>> getUnitsInBattleSortedToPrint() const;
  // [[nodiscard]] const std::vector<std::reference_wrapper<UnitStack>> getRoundQueue() const;
  [[nodiscard]] const UnitStack* getUnitInAction() const noexcept;
  [[nodiscard]] UnitStack* getUnitInAction() noexcept;
  [[nodiscard]] const Character* getCurrentCharacter() const noexcept;
  [[nodiscard]] Character* getCurrentCharacter() noexcept;
  [[nodiscard]] std::vector<UserCommand> getPossibleMoves() const noexcept;
  void setPossibleMoves( std::vector<UserCommand> ) noexcept;
  [[nodiscard]] bool isSameArmy( const UnitStack& unit1, const UnitStack& unit2 ) const noexcept;
  [[nodiscard]] Character& getUnitStackOwner( const UnitStack& ) const noexcept;
  [[nodiscard]] bool isAIMove() const;
  void forceUnplaceUnitStacks();
  void forcePlaceUnitStack( UnitStack& unit_stack, CoordPair new_coords );
  [[nodiscard]] bool isFinished() const noexcept;
  [[nodiscard]] std::shared_ptr<Battle> copy();
};