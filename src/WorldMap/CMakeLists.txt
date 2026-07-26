add_library(WorldMap
    WorldMap.cc
    MapObject.cc
    Building.cc
    GridTile.cc
    OverworldObstacle.cc
)

target_include_directories(WorldMap PUBLIC
    SFML::Graphic
    ${CMAKE_SOURCE_DIR}/include/WorldMap
    ${CMAKE_SOURCE_DIR}/include/Miscellaneous
    ${CMAKE_SOURCE_DIR}/include/
)

target_link_libraries(WorldMap PRIVATE Miscellaneous)