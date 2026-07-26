#include "Battle/Battle.h"

#include <sys/types.h>

#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <vector>

#include "Battle/BattleField.h"
#include "Battle/Tile.h"
#include "Character/Character.h"
#include "Exceptions/_NotImplementedException.hpp"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "Unit/Unit.h"

void Battle::setAttackingArmy() {
  auto& party = attacker_->getParty();
  for ( uint32_t i = 0; i < MAX_PARTY_SIZE; i++ ) {
    if ( party[i] == nullptr ) {
      continue;
    }
    CoordPair coords_in_battle = CoordPair( 0u, 0u );
    if ( i < 3 ) {
      coords_in_battle = CoordPair( 0u, i * 2 );
    } else if ( i == 3 ) {
      coords_in_battle = CoordPair( 0u, 5u );
    } else if ( i > 3 ) {
      coords_in_battle = CoordPair( 0u, ( i - 4 ) * 2 + 6 );
    }
    party[i]->setCoordsInBattle( coords_in_battle );
    battlefield_->getTileByProxy( coords_in_battle )->setObject( party[i] );
  }
}

void Battle::setDefendingArmy() {
  auto& party = defender_->getParty();
  for ( uint32_t i = 0; i < MAX_PARTY_SIZE; i++ ) {
    if ( party[i] == nullptr ) {
      continue;
    }
    CoordPair coords_in_battle = CoordPair( 0u, 0u );
    if ( i < 3 ) {
      coords_in_battle = CoordPair( 14u, i * 2 );
    } else if ( i == 3 ) {
      coords_in_battle = CoordPair( 14u, 5u );
    } else if ( i > 3 ) {
      coords_in_battle = CoordPair( 14u, ( i - 4 ) * 2 + 6 );
    }
    party[i]->setCoordsInBattle( coords_in_battle );
    battlefield_->getTileByProxy( coords_in_battle )->setObject( party[i] );
  }
}

uint32_t Battle::setUnitInQueue( std::shared_ptr<UnitStack> unit ) {
  uint32_t speed = unit->getSpeed();
  if ( round_queue_.size() == 0 ) {
    round_queue_.push_back( unit );
    return 0;
  } else {
    for ( auto it = round_queue_.begin(); it != round_queue_.end(); ++it ) {
      if ( ( *it )->getSpeed() < speed ) {
        round_queue_.insert( it, unit );
        return (uint)std::distance( round_queue_.begin(), it );
      }
    }
  }
  round_queue_.push_back( unit );
  return uint32_t( round_queue_.size() - 1 );
}
void Battle::createObstacles() {
  // create obstacles on battlefield
  // std::vector<std::shared_ptr<Tile>> tiles = battlefield_->getTiles();
  // for ( auto& tile : tiles ) {
  //   if ( tile->getCoords().x_ % 2 == 0 && tile->getCoords().y_ % 2 == 0 ) {
  //     tile->setObject( std::make_shared<Obstacle>( "Obstacle" ) );
  //   }
  // }
  throw NotImplementedException( "createObstacles" );
}

void Battle::nextRound() {
  // std::vector<std::shared_ptr<UnitStack>> active;
  // active.reserve(units_in_battle_.size());
  for ( auto& unit : getUnitsInBattle() ) {
    (void)setUnitInQueue( unit );  // TODO handle return value
  }
  ++round_counter_;
  attacker_threw_spell_ = false;
  defender_threw_spell_ = false;
}

Battle::Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
                std::shared_ptr<GridTile> background )
    : battlefield_( std::make_shared<BattleField>( background ) ), attacker_( attacker ), defender_( defender ) {
  // attacking_army_.reserve( 7 );
  // defending_army_.reserve( 7 );
  // units_in_battle_.reserve( 14 );
  setAttackingArmy();
  setDefendingArmy();
  nextUnit();
  state_ = BattleState::MOVING;
};

Battle::Battle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
                std::shared_ptr<GridTile> background, bool is_minimax )
    : Battle( attacker, defender, background ) {
  is_minimax_ = is_minimax;
}

sf::Texture& Battle::accept( Visitor& v ) const {
  return v.visit( *this );
}

BattleState Battle::getState() const {
  return state_;
}

bool Battle::setUnit( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords ) {
  std::shared_ptr<Tile> new_tile = battlefield_->getTileByProxy( new_coords );
  if ( new_tile == nullptr ) return false;
  new_tile->setObject( unit_stack );
  unit_stack->setCoordsInBattle( new_coords );
  return true;
}

bool Battle::killUnit( std::shared_ptr<UnitStack> unit_stack_to_kill ) {
  CoordPair coords = unit_stack_to_kill->getCoordsInBattle();
  bool attacker = isSameArmy( unit_stack_to_kill, getAttackingArmy()[0] );

  std::shared_ptr<Character> character = ( attacker ) ? attacker_ : defender_;

  for_each( character->getParty().begin(), character->getParty().end(), [&]( std::shared_ptr<UnitStack>& unit ) {
    if ( unit != nullptr && unit->getCoordsInBattle() == coords ) {
      // Remove the unit from the round_queue_
      getBattlefield()->getTileByProxy( coords )->setObject( nullptr );
      round_queue_.erase( std::remove( round_queue_.begin(), round_queue_.end(), unit_stack_to_kill ),
                          round_queue_.end() );
      unit->die();
      unit.reset();
    }
  } );
  if ( getAttackingArmy().size() == 0 ) {
    setBattleState( BattleState::WIN_DEFENDER );
    return true;
  }
  if ( getDefendingArmy().size() == 0 ) {
    setBattleState( BattleState::WIN_ATTACKER );
    return true;
  }
  return false;
}

void Battle::setBattleState( BattleState state ) {
  state_ = state;
}

bool Battle::move( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords ) {
  if ( !battlefield_ ) {
    throw std::runtime_error( "Battle::move while battlefield_==nullptr" );
  }
  CoordPair old_coords = unit_stack->getCoordsInBattle();

  std::shared_ptr<UnitStack> unit_stack_tmp = unit_stack;
  auto old_tile = battlefield_->getTileByProxy( old_coords );
  auto new_tile = battlefield_->getTileByProxy( new_coords );

  old_tile->setObject( nullptr );
  new_tile->setObject( unit_stack_tmp );

  unit_stack->setCoordsInBattle( new_coords );
  return true;
}

bool Battle::attack( std::shared_ptr<UnitStack> attacker, std::shared_ptr<UnitStack> defender ) {
  // in this attacker is the unit attacking not matter which champion attacked who
  // assertion checks if attacker and defender are in different armies
  auto attacking_army = getAttackingArmy();
  auto defending_army = getDefendingArmy();
  assert( !isSameArmy( attacker, defender ) );
  std::shared_ptr<const Unit> attacker_unit = attacker->getUnit();
  std::shared_ptr<const Unit> defender_unit = defender->getUnit();
  bool positive_luck = attacker->getLuck() > 0;
  bool luck = ( std::rand() % 100 ) < abs( attacker->getLuck() ) * 0.05 ? 1 : 0;
  double luck_multiplier = 1.0;
  if ( luck ) {
    if ( positive_luck ) {
      luck_multiplier = 2;
    } else {
      luck_multiplier = 0.5;
    }
  }
  int attack_defense = int( attacker_unit->getAttack() + attacker_->getAttack() ) - int( defender_unit->getDefense() )
                       - int( defender_->getDefense() );
  uint32_t positive_attack = uint32_t( std::max( 0, attack_defense ) );
  positive_attack = std::min( 60u, positive_attack );
  uint32_t positive_defense = uint32_t( std::max( 0, -attack_defense ) );
  positive_defense = std::min( 28u, positive_defense );
  uint32_t min_damage = attacker_unit->getMinDamage() * attacker->getSize();
  uint32_t max_damage = attacker_unit->getMaxDamage() * attacker->getSize();
  uint32_t attacker_dmg = min_damage + ( uint32_t( rand() ) % ( max_damage - min_damage + 1 ) );
  // dmg  = base DMG * size * (1+0.05*(attack-defense)) * (1-0.025*(defense-attack)) * luck_multiplier
  double dmg = double( attacker_dmg ) * ( 1.0 + 0.05 * double( positive_attack ) )
               * ( 1.0 - 0.025 * double( positive_defense ) ) * luck_multiplier;
  int dmg_rounded = static_cast<int>( dmg );
  if ( !defender->modifyCurrentHealth( dmg_rounded ) ) {
    return killUnit( defender );
  }
  return false;
}

std::shared_ptr<BattleField> Battle::getBattlefield() {
  return battlefield_;
}

std::shared_ptr<Character> Battle::getAttacker() const {
  return attacker_;
}

std::shared_ptr<Character> Battle::getDefender() const {
  return defender_;
}

size_t Battle::getRoundCounter() const {
  return round_counter_;
}

std::shared_ptr<UnitStack> Battle::getUnitFromCoords( CoordPair coords ) const {
  const std::vector<std::shared_ptr<UnitStack>> units = getUnitsInBattle();
  std::shared_ptr<UnitStack> unit = nullptr;
  if ( battlefield_->getTileByProxy( coords ) == nullptr ) return nullptr;
  std::for_each( units.begin(), units.end(), [&]( std::shared_ptr<UnitStack> unit_tmp ) {
    if ( coords == unit_tmp->getCoordsInBattle() ) unit = unit_tmp;
  } );
  return unit;
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
  unit_in_action_ = round_queue_.front();
  round_queue_.erase( round_queue_.begin() );
}

std::vector<std::shared_ptr<UnitStack>> Battle::getAttackingArmy() const {
  std::vector<std::shared_ptr<UnitStack>> attacking_army;
  for ( auto& unit_stack : attacker_->getParty() ) {
    if ( unit_stack != nullptr ) {
      attacking_army.push_back( unit_stack );
    }
  }
  return attacking_army;
}

std::vector<std::shared_ptr<UnitStack>> Battle::getDefendingArmy() const {
  std::vector<std::shared_ptr<UnitStack>> defending_army;
  for ( auto& unit_stack : defender_->getParty() ) {
    if ( unit_stack != nullptr ) {
      defending_army.push_back( unit_stack );
    }
  }
  return defending_army;
}

std::vector<std::shared_ptr<UnitStack>> Battle::getUnitsInBattle() const {
  std::vector<std::shared_ptr<UnitStack>> units_in_battle;
  for ( auto& unit_stack : getAttackingArmy() ) {
    units_in_battle.push_back( unit_stack );
  }
  for ( auto& unit_stack : getDefendingArmy() ) {
    units_in_battle.push_back( unit_stack );
  }
  return units_in_battle;
}

std::vector<std::shared_ptr<UnitStack>> Battle::getUnitsInBattleSortedToPrint() const {
  auto units_in_battle_sorted = getUnitsInBattle();
  std::sort( units_in_battle_sorted.begin(), units_in_battle_sorted.end(),
             []( const std::shared_ptr<UnitStack>& a, const std::shared_ptr<UnitStack>& b ) {
               if ( a->getCoordsInBattle().y_ == b->getCoordsInBattle().y_ ) {
                 return a->getCoordsInBattle().x_ >= b->getCoordsInBattle().x_;
               }
               return a->getCoordsInBattle().y_ >= b->getCoordsInBattle().y_;
             } );
  return units_in_battle_sorted;
}

std::vector<std::shared_ptr<UnitStack>> Battle::getRoundQueue() const {
  return round_queue_;
}

std::shared_ptr<UnitStack> Battle::getUnitInAction() const {
  return unit_in_action_;
}

std::vector<std::shared_ptr<Move>> Battle::getPossibleMoves() const {
  return possible_moves_;
}

BattleState Battle::getBattleState() const {
  return state_;
}

bool Battle::isSameArmy( const std::shared_ptr<UnitStack> unit1, const std::shared_ptr<UnitStack> unit2 ) const {
  const auto attacking_army = getAttackingArmy();
  const auto defending_army = getDefendingArmy();
  return ( std::find( attacking_army.begin(), attacking_army.end(), unit1 ) != attacking_army.end()
           && std::find( attacking_army.begin(), attacking_army.end(), unit2 ) != attacking_army.end() )
         || ( std::find( defending_army.begin(), defending_army.end(), unit1 ) != defending_army.end()
              && std::find( defending_army.begin(), defending_army.end(), unit2 ) != defending_army.end() );
}

bool Battle::isAIMove() const {
  return ( isSameArmy( unit_in_action_, attacker_->getParty()[0] ) && !attacker_->getIfUser() )
         || ( isSameArmy( unit_in_action_, defender_->getParty()[0] ) && !defender_->getIfUser() );
}

void Battle::forceUnplaceUnitStacks() {
  for ( uint32_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 0; y < MAP_HEIGHT_BF; ++y ) {
      auto tile = battlefield_->getTileByProxy( CoordPair( x, y ) );
      tile->setObject( nullptr );
    }
  }
  for ( auto unit_stack : getAttackingArmy() ) {
    unit_stack->setCoordsInBattle( BATTLE_MAP_NOT_FOUND_COORDS );
  }
  for ( auto unit_stack : getDefendingArmy() ) {
    unit_stack->setCoordsInBattle( BATTLE_MAP_NOT_FOUND_COORDS );
  }
}

void Battle::forcePlaceUnitStack( std::shared_ptr<UnitStack> unit_stack, CoordPair new_coords ) {
  auto tile = battlefield_->getTileByProxy( new_coords );
  tile->setObject( unit_stack );
  unit_stack->setCoordsInBattle( new_coords );
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
    CoordPair new_coords = units_in_battle_old[i]->getCoordsInBattle();
    auto unit_stack_new = units_in_battle_new[i];
    copy->forcePlaceUnitStack( unit_stack_new, new_coords );

    auto unit_stack_old = units_in_battle_old[i];
    if ( unit_stack_old == this->unit_in_action_ ) {
      copy->unit_in_action_ = unit_stack_new;
    }
  }
  auto& round_queue_old = this->round_queue_;
  auto& round_queue_new = copy->round_queue_;

  for ( uint32_t i = 0; i < round_queue_old.size(); ++i ) {
    for ( uint32_t j = 0; j < units_in_battle_old.size(); ++j ) {
      if ( round_queue_old[i] == units_in_battle_old[j] ) {
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