add_library(WorldMap SHARED
    WorldMap.cc
    Building.cc
    OverworldObstacle.cc
)

target_include_directories(WorldMap PRIVATE
)

target_link_libraries(WorldMap PUBLIC
    Miscellaneous
)

target_link_libraries(WorldMap PRIVATE 
    Character
    SFML::Graphics
)