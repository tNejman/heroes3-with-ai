add_library(Artifact SHARED
    Artifact.cc
)

target_include_directories(Artifact PRIVATE
)

target_link_libraries(Artifact PRIVATE
    Coords
    MapObject
)

target_link_libraries(Artifact PUBLIC
    magic_enum::magic_enum
)