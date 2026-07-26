add_library(Battle
    Battle.cc
    Battlefield.cc
    Tile.cc
    TileObject.cc
    Moves/AttackMove.cc
    Moves/MoveMove.cc
    Moves/MoveFactory.cc
    Moves/WaitMove.cc
)

target_include_directories(Battle PUBLIC
    SFML::Graphic
    ${CMAKE_SOURCE_DIR}/include/Battle/Moves
    ${CMAKE_SOURCE_DIR}/include/Battle/
    ${CMAKE_SOURCE_DIR}/include/
)

target_link_libraries(Battle PRIVATE Units Characters)