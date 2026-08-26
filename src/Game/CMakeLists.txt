add_library(Game SHARED
    Game.cc
    GameContext.cc
    GameStateBattle.cc
    GameStateOverworld.cc
    GameStateStack.cc
)

target_include_directories(Game PRIVATE
)

target_link_libraries(Game PRIVATE 
    # Algorithms
    Miscellaneous
    LoadAndSaveTools
)