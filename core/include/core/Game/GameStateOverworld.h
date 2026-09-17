#pragma once

#include <memory>
#include <vector>

#include "core/Game/GameCommand.h"
#include "core/Game/GameContext.h"
#include "core/Game/IGameState.h"
#include "core/Game/UserCommand.h"
#include "engine/Graphics/IRVisitor.h"
#include "engine/Graphics/Visitor.h"
#include "core/WorldMap/WorldMap.h"

class GameStateOverworld : public IGameState {
  WorldMap map_;

  struct CtorKey {
    explicit CtorKey() = default;
  };

 public:
  explicit GameStateOverworld( CtorKey, WorldMap&& world_map ) noexcept;

  [[nodiscard]] static GameStateOverworld create() noexcept;
  [[nodiscard]] static std::unique_ptr<IGameState> createUniqueptr() noexcept;

  [[nodiscard]] std::vector<UserCommand> legalCommands() const noexcept override;
  [[nodiscard]] StateTransition applyCommand( const UserCommand& command, GameContext& context ) noexcept override;
  [[nodiscard]] bool isLegalCommand( const UserCommand& command ) const noexcept override;

  void applyGameCommand( const GameCommand& command, GameContext& context ) noexcept override;

  void accept( IRVisitor& v ) const noexcept override;

  [[nodiscard]] const WorldMap& viewMap() const noexcept;

  void loadObstacles( std::vector<std::shared_ptr<OverworldObstacle>>& );  // TODO remove
};