#include "Game/Game.h"

void Game::_performGameLoopIterationOverworld() {
  key_handler_->monitorKeyPresses();
  ShiftPair move_delta = key_handler_->getMove();

  for (auto & player : players_) {
    for (auto it = player->getCharacters().begin(); it != player->getCharacters().end(); ++it) {
      bool all_empty = true;
      for (auto & unit : (*it)->getParty()) {
        if (unit) all_empty = false;
      }
      if (all_empty) {
        world_map_->setMapObject((*it)->getCoords(), nullptr);
        player->getCharacters().erase(it);
        break;
      }
    }
  }

  CoordPair center_coords = getMainPlayerCoords();
  if ( move_delta != ShiftPair( 0, 0 ) ) {
    try {
      world_map_->moveMapObject( getMainPlayerCoords(), move_delta );
      center_coords = getMainPlayerCoords();
      // std::cout << "DEBUG: Game moves character to: x=" << center_coords.x_ << " y=" << center_coords.y_ << std::endl;
    } catch ( const CoordinateOutOfBoundsException& e ) {
      std::cout << e.what() << std::endl;
    } catch ( const InvalidMoveException& e ) {
      try {
        auto player_coords = getMainPlayerCoords();
        CoordPair new_coords = player_coords + move_delta;  // exception caught earlier, this is safe
        auto new_tile_obj = world_map_->getTile( new_coords )->getMapObject();
        if ( new_tile_obj != nullptr ) {
          if ( auto character_ptr = std::dynamic_pointer_cast<Character>( new_tile_obj ) ) {
            startBattle( players_[0]->getCharacters()[0], character_ptr, world_map_->getTile( new_coords ) );
          }
        }
        std::cout << e.what() << std::endl;
      } catch ( const std::exception& start_battle_failed_exception ) {
        std::cout << "Game::_performGameLoopIterationOverworld() failed to start battle" << start_battle_failed_exception.what() << std::endl;
      }
    }
  }
  map_renderer_->render( *render_window_, center_coords );
}

void Game::_performGameLoopIterationBattle() {
  if ( battle_->getAttackingArmy().size() == 0 ||
       battle_->getDefendingArmy().size() == 0 ) {
    game_state_ = GameState::OVERWORLD;
    battle_.reset();
    return;
  }
  if ( battle_->getState() == BattleState::WIN_ATTACKER ||
       battle_->getState() == BattleState::WIN_ATTACKER ) {
    battle_.reset();
    game_state_ = GameState::OVERWORLD;
    return;
  }
  auto moves = MoveFactory::generateMoves( battle_ );

  sf::Sprite s = sf::Sprite( battle_->accept( *sprite_visitor_ ) );
  render_window_->draw( s );

  if ( battle_->isAIMove() ) {
    _performBattleAIMove();
  } else {
    _performBattleUserMove();
  }
}

void Game::_performBattleAIMove() {
  auto moves = MoveFactory::generateMoves( battle_ );
  std::shared_ptr<Move> best_move = nullptr;
  for ( auto& move : moves ) {
    if ( auto move_atk = std::dynamic_pointer_cast<AttackMove>( move ) ) {
      best_move = move;
      break;
    }
  }
  if ( best_move == nullptr )
    best_move = minimax_->getBestMove( battle_, MINIMAX_MAX_DEPTH );
  best_move->execute( battle_ );
}

void Game::_performBattleUserMove() {
  auto moves = MoveFactory::generateMoves( battle_ );
  // if ( waiting_for_print_ ) {
  //   for ( auto& move : moves ) {
  //     std::cout << "DEBUG: possible move: " << move->getInfo( battle_ ) << std::endl;
  //   }
  //   waiting_for_print_ = false;
  // }
  auto battle_coords = getCoordsFromClick();
  if ( battle_coords.has_value() ) {
    auto it = std::find_if( moves.begin(), moves.end(),
                            [&]( std::shared_ptr<Move> move ) {
                              return move->destinationCoords() == battle_coords.value();
                            } );

    if ( it != moves.end() ) {
      std::cout << "DEBUG: executing: " << ( *it )->getInfo( battle_ ) << std::endl;
      ( *it )->execute( battle_ );
      waiting_for_print_ = true;
    }
  }
}

void Game::placeCharactersOnWorldMap() {
  // const auto& main_character_ptr = players_[0]->getCharacters()[0];
  // world_map_->setMapObject( CoordPair( 0u, 0u ), character_ptr );
  for ( const auto& player_ptr : players_ ) {
    for ( const auto& character_ptr : player_ptr->getCharacters() ) {
      CoordPair character_coords = character_ptr->getCoords();
      world_map_->setMapObject( character_coords, character_ptr );
    }
  }
}

bool Game::pointInHexagon( int px, int py, double hex_x, double hex_y ) const {
  double dx = std::abs( px - hex_x );
  double dy = std::abs( py - hex_y );

  double dx_squared = dx * dx;
  double dy_squared = dy * dy;

  double distance_diagonal = std::sqrt( dx_squared + dy_squared );

  return distance_diagonal <= HEXAGON_SPRITE_MAX_RADIUS;
}

std::optional<CoordPair> Game::getCoordsFromClick() {
  if ( mouse_x_ < 0 || mouse_y_ < 0 ) {
    return std::nullopt;
  }

  CoordPair found_coords = BATTLE_MAP_NOT_FOUND_COORDS;

  for ( uint32_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 0; y < MAP_HEIGHT_BF; ++y ) {
      uint32_t offset_x_temp, offset_y_temp;
      // set offset for even rows
      offset_x_temp = BATTLE_MAP_SPRITE_INITAL_OFFSET_X_ODD + x * BATTLE_MAP_SPRITE_X_DELTA;
      offset_y_temp = BATTLE_MAP_SPRITE_INITAL_OFFSET_Y_ODD + ( 5 - y / 2 ) * BATTLE_MAP_SPRITE_Y_DELTA;

      // adjust if even
      if ( ( y % 2 == 0 ) ) {
        offset_x_temp += BATTLE_MAP_SPRITE_ADJUST_EVEN_X;
        offset_y_temp += BATTLE_MAP_SPRITE_ADJUST_EVEN_Y;
      }
      double hex_center_x = double( offset_x_temp ) + HEXAGON_SPRITE_WIDTH / 2.0;
      double hex_center_y = double( offset_y_temp ) + HEXAGON_SPRITE_HEIGHT / 2.0;

      if ( pointInHexagon( mouse_x_, mouse_y_, hex_center_x, hex_center_y ) ) {
        found_coords = CoordPair( x, y );
      }
    }
  }
  if ( found_coords == BATTLE_MAP_NOT_FOUND_COORDS ) {
    return std::nullopt;
  } else {
    mouse_x_ = -1;
    mouse_y_ = -1;
    // std::cout << "DEBUG: Game::handleMouseClick() found coords: x=" << found_coords.x_ << " y=" << found_coords.y_ << std::endl;
    return found_coords;
  }
}

void Game::startBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, std::shared_ptr<GridTile> background ) {
  battle_ = std::make_shared<Battle>( attacker, defender, background );
  game_state_ = GameState::BATTLE;
  waiting_for_print_ = true;
}

Game::Game( std::vector<std::shared_ptr<Player>> players )
    : Game( players, false ) {}

Game::Game( std::vector<std::shared_ptr<Player>> players, bool if_buffered_input )
    : players_( std::move( players ) ),
      factions_( { std::make_unique<FactionForge>(), std::make_unique<FactionConflux>() } ),
      render_window_( std::make_shared<sf::RenderWindow>( sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), WINDOW_NAME, sf::Style::Titlebar | sf::Style::Close  ) ),
      sprite_visitor_( std::make_shared<SpriteVisitor>() ),
      key_handler_( std::make_shared<KeyHandler>( if_buffered_input ) ),
      minimax_( std::make_shared<MinimaxAI>() ) {
  render_window_->setFramerateLimit( 30 );
  std::unique_ptr<MapLoader> map_loader = std::make_unique<MapLoader>();
  world_map_ = map_loader->load( WORLD_MAP_INPUT_PATH );
  assert( world_map_ != nullptr );
  this->placeCharactersOnWorldMap();
  map_renderer_ = std::make_shared<MapRenderer>( sprite_visitor_, world_map_ );
}

void Game::loadObstacles( std::vector<std::shared_ptr<MapObject>>& obstacles ) {
  world_map_->loadObstacles( obstacles );
}

GameState Game::getState() const {
  return game_state_;
}

void Game::setMouseCoords( int x, int y ) {
  mouse_x_ = x;
  mouse_y_ = y;
}

void Game::performGameLoopIteration() {
  switch ( game_state_ ) {
    case GameState::OVERWORLD:
      _performGameLoopIterationOverworld();
      break;
    case GameState::BATTLE:
      _performGameLoopIterationBattle();
      break;
    default:
      throw UnknownStateException( "Game loop tried to perform action regarding forbidden game state" );
  }
}

CoordPair Game::getMainPlayerCoords() const {
  return players_[0]->getCharacters()[0]->getCoords();
}

std::shared_ptr<sf::RenderWindow> Game::getRenderWindow() {
  return this->render_window_;
}

void Game::debugStartBattle() {
  battle_ = std::make_shared<Battle>( players_[0]->getCharacters()[0], players_[1]->getCharacters()[0], world_map_->getTile( CoordPair( 0u, 0u ) ) );
  game_state_ = GameState::BATTLE;
  waiting_for_print_ = true;
}
