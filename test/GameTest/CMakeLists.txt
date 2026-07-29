f_add_test_executable(testKeyHandler testKeyHandler.cc)
target_link_libraries(testKeyHandler PRIVATE
    Game
    Battle
)