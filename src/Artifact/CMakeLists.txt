add_library(Artifact SHARED
    Artifact.cc
)

target_include_directories(Artifact PRIVATE
)

target_link_libraries(Artifact PRIVATE
    Miscellaneous
    MapObject
    SFML::Graphics
)