add_library(Battle SHARED
    Moves/AttackMove.cc
    Moves/MoveFactory.cc
    Moves/MoveMove.cc
    Moves/WaitMove.cc

    Battle.cc
    Battlefield.cc
    Tile.cc
)

target_include_directories(Battle PRIVATE
)

target_link_libraries(Battle PUBLIC
    Character
    Unit
)

target_link_libraries(Battle PRIVATE 
)