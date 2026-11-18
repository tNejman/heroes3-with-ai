#include "engine/model/IGame/TurnManager.h"

#include <memory>
#include <utility>
#include <vector>

#include "engine/model/IGame/ITurnEffect.hpp"

void TurnManager::removeExpiredEffects( std::vector<std::unique_ptr<ITurnEffect>>& effects ) noexcept {
  std::vector<std::unique_ptr<ITurnEffect>> only_non_expired{};
  only_non_expired.reserve( effects.size() );

  for ( auto& effect : effects ) {
    if ( effect->duration_.type_ == ITurnEffect::Duration::Type::N_TURNS && effect->duration_.n_duration_ == 0 ) {
      continue;
    }
    only_non_expired.push_back( std::move( effect ) );
  }

  std::swap( effects, only_non_expired );
}

void TurnManager::updateEffectDuration( ITurnEffect& effect ) noexcept {
  // assumes all n_durations are positive
  switch ( effect.duration_.type_ ) {
    case ITurnEffect::Duration::Type::PERMANENT: return;
    case ITurnEffect::Duration::Type::N_TURNS: effect.duration_.n_duration_ -= 1; break;
  }
}

void TurnManager::performEffects( std::vector<std::unique_ptr<ITurnEffect>>& effects ) noexcept {
  for ( auto& effect : effects ) {
    effect->apply();
    updateEffectDuration( *effect );
  }
  removeExpiredEffects( effects );
}

/* ==== @PUBLIC ==== */

void TurnManager::performEffects( TurnEffectType turn_effect_type ) noexcept {
  switch ( turn_effect_type ) {
    case TurnEffectType::END_OF_TURN: performEffects( end_of_turn_effects_ ); break;
    case TurnEffectType::BEGINNING_OF_TURN: performEffects( beggining_of_turn_effects_ ); break;
  }
}