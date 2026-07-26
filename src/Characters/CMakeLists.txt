add_library(Characters
    Character.cc
    SecondarySkill.cc
)

target_include_directories(Characters PUBLIC
    SFML::Graphic
    ${CMAKE_SOURCE_DIR}/include/Characters
    ${CMAKE_SOURCE_DIR}/include/Magic
    ${CMAKE_SOURCE_DIR}/include/Units
    ${CMAKE_SOURCE_DIR}/include/WorldMap
    ${CMAKE_SOURCE_DIR}/include/
)
target_link_libraries(Characters PRIVATE Artifacts Magic Units WorldMap)
