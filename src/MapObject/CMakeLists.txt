add_library(MapObject SHARED
    MapObject.cc
)

target_link_libraries(MapObject PRIVATE
    SFML::Graphics
)