add_library(Battle SHARED
    Battle.cc
    Battlefield.cc
    Tile.cc
    TileObject.cc
    Moves/AttackMove.cc
    Moves/MoveMove.cc
    Moves/MoveFactory.cc
    Moves/WaitMove.cc
)

target_include_directories(Battle PRIVATE
)

target_link_libraries(Battle PUBLIC
    Character
    Unit
)

target_link_libraries(Battle PRIVATE 
    SFML::Graphics
)