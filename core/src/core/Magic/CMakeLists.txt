add_library(Magic SHARED
    SpellBook.cc
    Spell.cc
)

target_include_directories(Magic PRIVATE
    magic_enum::magic_enum
)

target_link_libraries(Magic PRIVATE
    magic_enum::magic_enum
)
