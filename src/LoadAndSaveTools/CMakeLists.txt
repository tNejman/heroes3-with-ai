add_library(LoadAndSaveTools SHARED
    CharacterSaver.cc
    MapSaver.cc
    MapLoader.cc
)

target_include_directories(LoadAndSaveTools PRIVATE
)

target_link_libraries(LoadAndSaveTools PRIVATE
    Character
    Magic
    SFML::Graphics
)