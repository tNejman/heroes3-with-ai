#include <gtest/gtest.h>

#include <SFML/Window/Keyboard.hpp>
#include <memory>

#include "Game/KeyHandler.h"
#include "Miscellaneous/ProjectLib.h"

TEST( KeyHandlerTest, mockInput ) {
  auto key_handler = std::make_shared<KeyHandler>( true, true );
  auto mock_input = std::make_shared<MockKeyboardInput>();

  // frame 1
  mock_input->set( { W } );
  key_handler->debugMockInput( mock_input );
  key_handler->monitorKeyPresses();
  auto move_direction_frame1 = key_handler->getMove();
  ASSERT_EQ( CharacterMoveDirection::NONE, move_direction_frame1 );

  // for frames 2,3,4...
  mock_input->set( {} );
  key_handler->debugMockInput( mock_input );

  // frame 2 (buffer 1/5)
  key_handler->monitorKeyPresses();
  auto move_direction_frame2 = key_handler->getMove();
  ASSERT_EQ( CharacterMoveDirection::NONE, move_direction_frame2 );

  // frame 3 (buffer 2/5)
  key_handler->monitorKeyPresses();
  auto move_direction_frame3 = key_handler->getMove();
  ASSERT_EQ( CharacterMoveDirection::NONE, move_direction_frame3 );

  // frame 4 (buffer 3/5)
  key_handler->monitorKeyPresses();
  auto move_direction_frame4 = key_handler->getMove();
  ASSERT_EQ( CharacterMoveDirection::NONE, move_direction_frame4 );

  // frame 5 (buffer 4/5)
  key_handler->monitorKeyPresses();
  auto move_direction_frame5 = key_handler->getMove();
  ASSERT_EQ( CharacterMoveDirection::NONE, move_direction_frame5 );

  // frame 6 (buffer 5/5)
  key_handler->monitorKeyPresses();
  auto move_direction_frame6 = key_handler->getMove();
  // ASSERT_EQ( CharacterMoveDirection::UP, move_direction_frame6 );
}

// TEST( KeyHandlerTest, mockInput ) {
//   auto key_handler = std::make_shared<KeyHandler>( true, true );
//   // frame 1
//   // frame 2
//   // frame 3
//   // frame 4
//   // frame 5
//   // frame 6
//   // frame 7
//   // frame 8
//   // frame 9
//   // frame 10
// }
