add_library(WorldMap SHARED
    WorldMap.cc
    Building.cc
    OverworldObstacle.cc
)

target_include_directories(WorldMap PRIVATE
)

target_link_libraries(WorldMap PUBLIC
    Character
    Coords
)
