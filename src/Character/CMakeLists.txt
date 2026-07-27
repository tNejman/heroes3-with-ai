add_library(Character SHARED
    Character.cc
    SecondarySkill.cc
)

target_include_directories(Character PRIVATE
)

target_link_libraries(Character PUBLIC
    Artifact
    Miscellaneous
    Unit
    MapObject
)

target_link_libraries(Character PRIVATE
    Magic
    SFML::Graphics
)
