add_library(LoadAndSaveTools
    CharacterSaver.cc
    MapSaver.cc
    MapLoader.cc
)

target_include_directories(LoadAndSaveTools PUBLIC
    SFML::Graphic
    ${CMAKE_SOURCE_DIR}/include/Characters
    ${CMAKE_SOURCE_DIR}/include/LoadAndSaveTools
    ${CMAKE_SOURCE_DIR}/include/
)

target_link_libraries(LoadAndSaveTools PRIVATE
    Characters
    Magic
)