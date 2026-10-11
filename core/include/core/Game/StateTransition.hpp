#pragma once

#include <engine/IGame/Coords.h>

#include <variant>

#include "aux/IsVariantMember.hpp"
#include "core/Misc/ProjectLib.h"

namespace game {

namespace state_transition {

using NoTransition = std::monostate;

struct PopState {};

struct RequestBattle {
  int attacker_id_;
  int defender_id_;
  CoordPair at_;
  Terrain terrain_;
};

};  // namespace state_transition

struct StateTransition {
  using V = std::variant<state_transition::NoTransition, state_transition::PopState, state_transition::RequestBattle>;
  V transition_;

  template <typename T>
  requires( IS_VARIANT_MEMBER_V<T, V> )
  StateTransition( T opt ) : transition_( opt ) {
  }
};

};  // namespace game