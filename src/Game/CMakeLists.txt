add_library(Game SHARED
    KeyHandler.cc
    Game.cc
)

target_include_directories(Game PRIVATE
)

target_link_libraries(Game PRIVATE 
    # Algorithms
    Graphics
    Miscellaneous
)