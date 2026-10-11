#pragma once

#include <memory>
#include <vector>

#include "core/Game/Context.h"
#include "core/Game/SystemCommand.h"
#include "core/Game/UserCommand.hpp"
#include "core/WorldMap/WorldMap.h"
#include "engine/Graphics/IRVisitor.h"
#include "engine/Graphics/Visitor.h"
#include "engine/IGame/IState.h"

namespace game {

// class StateOverworld : public game::StateOf<WorldMapCommand, WorldMapSystemCommand> {
class StateOverworld : public IState {
 private:
  WorldMap map_;

  struct CtorKey {
    explicit CtorKey() = default;
  };

 public:
  /**
   * @brief Construct a new State Overworld object
   * @note std::make_unique requires public ctor; key is to forbid creation other than through create methods
   */
  explicit StateOverworld( CtorKey, WorldMap&& world_map ) noexcept;

  [[nodiscard]] bool isCommandForThisState( const game::UserCommand& command ) const noexcept override;
  [[nodiscard]] bool isCommandForThisState( const game::SystemCommand& command ) const noexcept override;

  [[nodiscard]] static game::StateOverworld create() noexcept;
  [[nodiscard]] static std::unique_ptr<game::IState> createUniqueptr() noexcept;

  [[nodiscard]] std::vector<UserCommand> legalCommands() const noexcept override;
  [[nodiscard]] game::StateTransition applyCommand( const game::UserCommand& command,
                                                    game::Context& context ) noexcept override;
  [[nodiscard]] bool isLegalCommand( const UserCommand& command ) const noexcept override;

  void applySystemCommand( const SystemCommand& command, game::Context& context ) noexcept override;

  void accept( IRVisitor& v ) const noexcept override;

  [[nodiscard]] const WorldMap& viewMap() const noexcept;

  void loadObstacles( std::vector<std::shared_ptr<OverworldObstacle>>& );  // TODO remove
};

}  // namespace game