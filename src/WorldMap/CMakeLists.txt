add_library(WorldMap SHARED
    WorldMap.cc
    Building.cc
    GridTile.cc
    OverworldObstacle.cc
)

target_include_directories(WorldMap PRIVATE
)

target_link_libraries(WorldMap PRIVATE 
    Miscellaneous
    Character
    SFML::Graphics
)