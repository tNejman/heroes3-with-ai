f_add_test_executable(testBattle
  SOURCES testBattle.cc
  LIBRARIES Battle WorldMap MapObject
  REFLECTION
)

f_add_test_executable(testBattlefield
  SOURCES testBattlefield.cc
  LIBRARIES Battle Coords
)
