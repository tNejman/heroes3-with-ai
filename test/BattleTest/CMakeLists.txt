f_add_test_executable(testBattle testBattle.cc)
target_link_libraries(testBattle PRIVATE
    Battle
)

f_add_test_executable(testBattlefield testBattlefield.cc)
target_link_libraries(testBattlefield PRIVATE
    Battle
)