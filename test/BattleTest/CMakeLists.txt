f_add_test_executable(testBattle testBattle.cc)
target_link_libraries(testBattle PRIVATE
    Battle
    WorldMap
    MapObject
)

f_add_test_executable(testBattlefield testBattlefield.cc)
target_link_libraries(testBattlefield PRIVATE
    Battle
    Miscellaneous
    WorldMap
    MapObject
)