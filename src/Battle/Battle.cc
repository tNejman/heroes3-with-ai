#include "Battle/Battle.h"

#include <X11/X.h>
#include <sys/types.h>

#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "Battle/BattleField.h"
#include "Battle/Tile.h"
#include "Character/Character.h"
#include "Character/CharacterArmy.h"
#include "Exceptions/Err.hpp"
#include "Exceptions/UnknownStateException.hpp"
#include "Exceptions/_NotImplementedException.hpp"
#include "Game/UserCommand.h"
#include "Graphics/Visitor.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "Unit/Unit.h"
#include "Unit/UnitsLib.h"

void Battle::setAttackingArmy() {
  auto& party = attacker_->army().getParty();
  for ( int i = 0; i < MAX_PARTY_SIZE; ++i ) {
    auto& maybe_unit = party[static_cast<size_t>( i )];
    if ( !maybe_unit ) {
      continue;
    }
    auto& stack = *maybe_unit;
    CoordPair coords_in_battle = ( i < 3 )    ? CoordPair{ 0, i * 2 }
                                 : ( i == 3 ) ? CoordPair{ 0, 5 }
                                              : CoordPair{ 0, ( ( i - 4 ) * 2 ) + 6 };
    battlefield_->getTileByProxy( coords_in_battle )->setObject( stack );
    stack.setCoordsInBattle( coords_in_battle );
  }
}

void Battle::setDefendingArmy() {
  auto& party = defender_->army().getParty();
  for ( int i = 0; i < MAX_PARTY_SIZE; ++i ) {
    auto& maybe_unit = party[static_cast<size_t>( i )];
    if ( !maybe_unit ) {
      continue;
    }
    auto& stack = *maybe_unit;
    CoordPair coords_in_battle = ( i < 3 )    ? CoordPair( 14, i * 2 )
                                 : ( i == 3 ) ? CoordPair( 14, 5 )
                                              : CoordPair( 14, ( ( i - 4 ) * 2 ) + 6 );

    battlefield_->getTileByProxy( coords_in_battle )->setObject( stack );
    stack.setCoordsInBattle( coords_in_battle );
  }
}

int Battle::setUnitInQueue( UnitStack& unit ) {
  int speed = unit.getData().speed_;
  if ( round_queue_.empty() ) {
    round_queue_.emplace_back( unit );
    return 0;
  }
  for ( auto it = round_queue_.begin(); it != round_queue_.end(); ++it ) {
    if ( ( *it ).get().getData().speed_ < speed ) {
      round_queue_.insert( it, unit );
      return static_cast<int>( std::distance( round_queue_.begin(), it ) );
    }
  }
  round_queue_.emplace_back( unit );
  return static_cast<int>( round_queue_.size() - 1 );
}
void Battle::createObstacles() {
  // create obstacles on battlefield
  // std::vector<std::shared_ptr<Tile>> tiles = battlefield_->getTiles();
  // for ( auto& tile : tiles ) {
  //   if ( tile->getCoords().x_ % 2 == 0 && tile->getCoords().y_ % 2 == 0 ) {
  //     tile->setObject( std::make_shared<Obstacle>( "Obstacle" ) );
  //   }
  // }
  err::raise<NotImplementedException>();
}

void Battle::nextRound() {
  // std::vector<std::shared_ptr<UnitStack>> active;
  // active.reserve(units_in_battle_.size());
  for ( auto& unit : getUnitsInBattle() ) {
    setUnitInQueue( unit );
  }
  ++round_counter_;
  attacker_threw_spell_ = false;
  defender_threw_spell_ = false;
}

[[nodiscard]] bool Battle::isMoveLegal( const BattleCommand& command ) const noexcept {
  // TODO account for obstacles
  const auto is_free_destination = battlefield_->getTileByProxy( command.destination )->getObject() == nullptr;
  const auto is_distance_in_speed_range =
      command.destination.distanceFrom( unit_in_action_->getCoordsInBattle() ) <= unit_in_action_->getData().speed_;
  return is_free_destination && is_distance_in_speed_range;
  // err::raise<NotImplementedException>();
}
[[nodiscard]] bool Battle::isAttackLegal( const BattleCommand& bc ) const noexcept {
  /**
   * @TODO
   * check ammo
   * check big units distance
   * check dead unit/obstacle
   */
  assert( unit_in_action_ != nullptr && "Battle::isAttackLegal -> battle.unit_in_action is nullptr" );
  if ( state_ != BattleState::ATTACKING ) {
    return false;
  }
  const auto* const target = getUnitFromCoords( bc.destination );
  if ( target == nullptr || isSameArmy( *unit_in_action_, *target ) ) {
    return false;
  }
  const bool is_ranged_unit = unit_in_action_->getData().is_range_;
  const bool next_to_defender = unit_in_action_->getCoordsInBattle().distanceFrom( bc.destination ) < 2;
  const bool is_unit_blocked = isUnitBlocked( *unit_in_action_ );

  return next_to_defender || ( is_ranged_unit && !is_unit_blocked );
}
[[nodiscard]] bool Battle::isWaitLegal( const BattleCommand& ) const noexcept {
  // TODO actually write logic
  return true;
}

/* === @PUBLIC === */

Battle::Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, Terrain background )
    : state_( BattleState::MOVING ),
      battlefield_( std::make_shared<BattleField>( background ) ),
      attacker_( std::move( attacker ) ),
      defender_( std::move( defender ) ),
      attacker_threw_spell_( false ),
      defender_threw_spell_( false ) {
  round_queue_.reserve( static_cast<size_t>( MAX_PARTY_SIZE ) * 2 );
  setAttackingArmy();
  setDefendingArmy();
  nextUnit();
  assert( attacker_.get() != defender_.get() );
};

Battle::Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, Terrain background,
                bool is_minimax )
    : Battle( std::move( attacker ), std::move( defender ), background ) {
  is_minimax_ = is_minimax;
}

sf::Texture& Battle::accept( Visitor& v ) const {
  return v.visit( *this );
}

BattleState Battle::getState() const {
  return state_;
}

bool Battle::setUnit( UnitStack& unit_stack, CoordPair new_coords ) {
  std::shared_ptr<Tile> new_tile = battlefield_->getTileByProxy( new_coords );
  if ( new_tile == nullptr ) {
    return false;
  }
  new_tile->setObject( unit_stack );
  unit_stack.setCoordsInBattle( new_coords );
  return true;
}

bool Battle::killUnit( UnitStack& unit_stack_to_kill ) {
  bool attacker = isSameArmy( unit_stack_to_kill, getAttackingArmy()[0] );

  std::shared_ptr<Character> character = ( attacker ) ? attacker_ : defender_;

  std::for_each(
      character->army().getParty().begin(), character->army().getParty().end(), [&]( std::optional<UnitStack>& unit ) {
        if ( unit && &*unit == &( unit_stack_to_kill ) )  // compare addresses, must kill the exactly same unit
        {
          // Remove the unit from the round_queue_
          getBattlefield()->getTileByProxy( unit_stack_to_kill.getCoordsInBattle() )->resetObject();
          std::erase_if( round_queue_, [target = std::addressof( unit_stack_to_kill )]( const UnitStack& ref ) {
            return std::addressof( ref ) == target;
          } );
          unit.reset();
        }
      } );
  if ( getAttackingArmy().empty() ) {
    setBattleState( BattleState::WIN_DEFENDER );
    return true;
  }
  if ( getDefendingArmy().empty() ) {
    setBattleState( BattleState::WIN_ATTACKER );
    return true;
  }
  return false;
}

void Battle::setBattleState( BattleState state ) {
  state_ = state;
}

bool Battle::move( UnitStack& unit_stack, CoordPair new_coords ) {
  if ( !battlefield_ ) {
    err::raise<UnknownStateException>( "expected battlefield_ to be initialized but is nullptr" );
  }
  CoordPair old_coords = unit_stack.getCoordsInBattle();

  auto& unit_stack_tmp = unit_stack;
  auto old_tile = battlefield_->getTileByProxy( old_coords );
  auto new_tile = battlefield_->getTileByProxy( new_coords );

  old_tile->resetObject();
  new_tile->setObject( unit_stack_tmp );

  unit_stack.setCoordsInBattle( new_coords );
  return true;
}

bool Battle::attack( UnitStack& attacker, UnitStack& defender ) {
  // in this attacker is the unit attacking not matter which champion attacked who
  // assertion checks if attacker and defender are in different armies
  auto attacking_army = getAttackingArmy();
  auto defending_army = getDefendingArmy();
  assert( !isSameArmy( attacker, defender ) );
  const auto& attacker_unit = attacker.getData();
  const auto& defender_unit = defender.getData();
  bool positive_luck = attacker.getLuck() > 0;
  bool luck = ( std::rand() % 100 ) < std::abs( attacker.getLuck() ) * 0.05 ? 1 : 0;
  double luck_multiplier = 1.0;
  if ( luck ) {
    if ( positive_luck ) {
      luck_multiplier = 2.0;
    } else {
      luck_multiplier = 0.5;
    }
  }
  int attack_defense = attacker_unit.attack_ + attacker_->stats().getPrimarySkills().attack_ - defender_unit.defense_
                       - defender_->stats().getPrimarySkills().defense_;
  int positive_attack = std::max( 0, attack_defense );
  positive_attack = std::min( 60, positive_attack );
  int positive_defense = std::max( 0, -attack_defense );
  positive_defense = std::min( 28, positive_defense );
  int min_damage = attacker_unit.min_damage_ * attacker.getSize();
  int max_damage = attacker_unit.max_damage_ * attacker.getSize();
  int attacker_dmg = min_damage + ( rand() % ( max_damage - min_damage + 1 ) );
  // dmg  = base DMG * size * (1+0.05*(attack-defense)) * (1-0.025*(defense-attack)) * luck_multiplier
  double dmg = static_cast<double>( attacker_dmg ) * ( 1.0 + ( 0.05 * static_cast<double>( positive_attack ) ) )
               * ( 1.0 - ( 0.025 * static_cast<double>( positive_defense ) ) ) * luck_multiplier;
  int dmg_rounded = static_cast<int>( dmg );
  defender.modifyCurrentHealth( dmg_rounded );
  if ( !defender.isAlive() ) {
    return killUnit( defender );
  }
  return false;
}

[[nodiscard]] bool Battle::isUnitBlocked( const UnitStack& stack ) const noexcept {
  const auto neighbours = battlefield_->getTileNeighbours( stack.getCoordsInBattle() );
  // find one with unit on it
  const auto it = std::ranges::find_if( neighbours, [&]( const std::shared_ptr<Tile>& tile ) {
    if ( !tile ) {
      return false;
    }
    auto* const object = tile->getObject();
    if ( !object ) {
      return false;
    }
    return object->asUnit() != nullptr && !isSameArmy( *object->asUnit(), stack );
  } );
  return it != neighbours.end();
}

[[nodiscard]] bool Battle::isLegalCommand( const BattleCommand& command ) const noexcept {
  if ( command.destination == unit_in_action_->getCoordsInBattle() ) {
    return isWaitLegal( command );
  }
  switch ( state_ ) {
    case BattleState::ATTACKING: return isAttackLegal( command );
    case BattleState::MOVING: return isMoveLegal( command );
    default: assert( false && "Battle::isLegalCommand -> reached unknown state" );
  }
}

std::shared_ptr<BattleField> Battle::getBattlefield() const noexcept {
  return battlefield_;
}

std::shared_ptr<BattleField> Battle::getBattlefield() noexcept {
  return battlefield_;
}

std::shared_ptr<Character> Battle::getAttacker() const {
  return attacker_;
}

std::shared_ptr<Character> Battle::getDefender() const {
  return defender_;
}

int Battle::getRoundCounter() const {
  return round_counter_;
}

const UnitStack* Battle::getUnitFromCoords( CoordPair coords ) const noexcept {
  auto* maybe_object = battlefield_->getTileByProxy( coords )->getObject();
  return ( maybe_object == nullptr ) ? nullptr : maybe_object->asUnit();
}
UnitStack* Battle::getUnitFromCoords( CoordPair coords ) noexcept {
  auto* maybe_object = battlefield_->getTileByProxy( coords )->getObject();
  return ( maybe_object == nullptr ) ? nullptr : maybe_object->asUnit();
}

bool Battle::hasAttackerThrownSpell() const {
  return attacker_threw_spell_;
}

bool Battle::hasDefenderThrownSpell() const {
  return defender_threw_spell_;
}

void Battle::nextUnit() {
  if ( round_queue_.empty() ) {
    nextRound();
  }
  unit_in_action_ = &( round_queue_.front().get() );
  round_queue_.erase( round_queue_.begin() );
}

std::vector<std::reference_wrapper<UnitStack>> Battle::getAttackingArmy() const {
  std::vector<std::reference_wrapper<UnitStack>> attacking_army;
  for ( auto& unit_stack : attacker_->army().getParty() ) {
    if ( unit_stack ) {
      attacking_army.emplace_back( *unit_stack );
    }
  }
  return attacking_army;
}

std::vector<std::reference_wrapper<UnitStack>> Battle::getDefendingArmy() const {
  std::vector<std::reference_wrapper<UnitStack>> defending_army;
  for ( auto& unit_stack : defender_->army().getParty() ) {
    if ( unit_stack ) {
      defending_army.emplace_back( *unit_stack );
    }
  }
  return defending_army;
}

std::vector<std::reference_wrapper<UnitStack>> Battle::getUnitsInBattle() const {
  std::vector<std::reference_wrapper<UnitStack>> units_in_battle;
  units_in_battle.reserve( static_cast<size_t>( MAX_PARTY_SIZE ) * 2 );
  units_in_battle.append_range( getAttackingArmy() );
  units_in_battle.append_range( getDefendingArmy() );
  return units_in_battle;
}

std::vector<std::reference_wrapper<UnitStack>> Battle::getUnitsInBattleSortedToPrint() const {
  auto units_in_battle_sorted = getUnitsInBattle();
  std::ranges::sort( units_in_battle_sorted, []( const UnitStack& a, const UnitStack& b ) {
    if ( a.getCoordsInBattle().y_ == b.getCoordsInBattle().y_ ) {
      return a.getCoordsInBattle().x_ >= b.getCoordsInBattle().x_;
    }
    return a.getCoordsInBattle().y_ >= b.getCoordsInBattle().y_;
  } );
  return units_in_battle_sorted;
  // std::vector<std::reference_wrapper<UnitStack>> units_in_battle_sorted;
  // units_in_battle_sorted.reserve( static_cast<size_t>( MAX_PARTY_SIZE ) * 2 );
  // for ( const auto& row : battlefield_->getGrid() ) {
  //   for ( const auto& tile : row ) {
  //     if ( tile->getObject() != nullptr ) {
  //       if ( const auto* object = tile->getObject()->asUnit() ) {
  //         units_in_battle_sorted.push_back( object->stack_ );
  //       }
  //     }
  //   }
  // }
  // return units_in_battle_sorted;
}

// std::vector<UnitStackWC> Battle::getRoundQueue() const {
//   return round_queue_;
// }

const UnitStack* Battle::getUnitInAction() const noexcept {
  return unit_in_action_;
}

UnitStack* Battle::getUnitInAction() noexcept {
  return unit_in_action_;
}

std::vector<std::shared_ptr<Move>> Battle::getPossibleMoves() const {
  return possible_moves_;
}

BattleState Battle::getBattleState() const {
  return state_;
}

bool Battle::isSameArmy( const UnitStack& unit1, const UnitStack& unit2 ) const {
  const auto attacking_army = getAttackingArmy();
  const auto defending_army = getDefendingArmy();

  auto is_unit_in_army = [&]( const std::vector<std::reference_wrapper<UnitStack>>& army, const UnitStack& stack ) {
    return std::ranges::find_if( army, [&]( const UnitStack& stack_in_army ) { return &stack_in_army == &stack; } )
           != army.end();
  };

  return ( is_unit_in_army( attacking_army, unit1 ) && is_unit_in_army( attacking_army, unit2 ) )
         || ( is_unit_in_army( defending_army, unit1 ) && is_unit_in_army( defending_army, unit2 ) );
}

bool Battle::isAIMove() const {
  if ( unit_in_action_ == nullptr ) {
    err::raise<UnknownStateException>( "unit in action is null" );
  }
  return ( isSameArmy( *unit_in_action_, attacker_->army().getParty()[0].value() ) && !attacker_->getIfUser() )
         || ( isSameArmy( *unit_in_action_, defender_->army().getParty()[0].value() ) && !defender_->getIfUser() );
}

void Battle::forceUnplaceUnitStacks() {
  for ( int x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( int y = 0; y < MAP_HEIGHT_BF; ++y ) {
      auto tile = battlefield_->getTileByProxy( CoordPair( x, y ) );
      tile->resetObject();
    }
  }
  // for ( const auto& unit_stack : getAttackingArmy() ) {
  //   unit_stack->setCoordsInBattle( BATTLE_MAP_NOT_FOUND_COORDS );
  // }
  // for ( const auto& unit_stack : getDefendingArmy() ) {
  //   unit_stack->setCoordsInBattle( BATTLE_MAP_NOT_FOUND_COORDS );
  // }
}

void Battle::forcePlaceUnitStack( UnitStack& unit_stack, CoordPair new_coords ) {
  auto tile = battlefield_->getTileByProxy( new_coords );
  tile->setObject( unit_stack );
  unit_stack.setCoordsInBattle( new_coords );
}

std::shared_ptr<Battle> Battle::copy() {
  auto attacker_copy = this->attacker_->copy();
  auto defender_copy = this->defender_->copy();
  std::shared_ptr<Battle> copy =
      std::make_shared<Battle>( attacker_copy, defender_copy, battlefield_->getBackground(), true );

  auto units_in_battle_old = this->getUnitsInBattle();
  auto units_in_battle_new = copy->getUnitsInBattle();
  assert( units_in_battle_old.size() == units_in_battle_new.size() );

  copy->forceUnplaceUnitStacks();
  copy->round_queue_.clear();

  for ( uint32_t i = 0; i < units_in_battle_new.size(); ++i ) {
    // new_coords from old units because old battle holds correct coordinates
    CoordPair new_coords = units_in_battle_old[i].get().getCoordsInBattle();
    UnitStack& unit_stack_new = units_in_battle_new[i];
    copy->forcePlaceUnitStack( unit_stack_new, new_coords );

    const UnitStack& unit_stack_old = units_in_battle_old[i];
    if ( &unit_stack_old == this->unit_in_action_ ) {
      copy->unit_in_action_ = &( unit_stack_new );
    }
  }
  auto& round_queue_old = this->round_queue_;
  auto& round_queue_new = copy->round_queue_;

  for ( const auto& i : round_queue_old ) {
    for ( uint32_t j = 0; j < units_in_battle_old.size(); ++j ) {
      if ( &i == &( units_in_battle_old[j] ) ) {
        round_queue_new.push_back( units_in_battle_new[j] );
      }
    }
  }

  // Deep copy possible_moves_
  copy->possible_moves_.clear();
  // Copy primitive and enum members
  copy->round_counter_ = round_counter_;
  copy->attacker_threw_spell_ = attacker_threw_spell_;
  copy->defender_threw_spell_ = defender_threw_spell_;
  copy->state_ = state_;

  return copy;
}