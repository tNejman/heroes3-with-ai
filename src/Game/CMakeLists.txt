add_library(Game SHARED
    Game.cc
    GameContext.cc
    GameStateBattle.cc
    GameStateOverworld.cc
    GameStateStack.cc
    KeyHandler.cc
    MouseHandler.cc
)

target_include_directories(Game PRIVATE
)

target_link_libraries(Game PRIVATE 
    # Algorithms
    Graphics
    Miscellaneous
    LoadAndSaveTools
)