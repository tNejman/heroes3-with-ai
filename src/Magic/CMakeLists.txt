add_library(Magic
    SpellBook.cc
    Spell.cc
)

target_include_directories(Magic PUBLIC
    SFML::Graphic
    ${CMAKE_SOURCE_DIR}/include/Magic
    ${CMAKE_SOURCE_DIR}/include/
)