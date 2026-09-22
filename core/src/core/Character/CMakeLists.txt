add_library(Character SHARED
    Character.cc
    CharacterArmy.cc
    CharacterBuilder.cc
    CharacterInventory.cc
    CharacterStats.cc
)

target_include_directories(Character PRIVATE
)

target_link_libraries(Character PUBLIC
    Artifact
    Coords
    Unit
    Magic
    MapObject
)
