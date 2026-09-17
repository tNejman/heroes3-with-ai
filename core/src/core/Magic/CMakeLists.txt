add_library(Magic SHARED
    SpellBook.cc
    Spell.cc
)

target_include_directories(Magic PRIVATE
)

target_link_libraries(Magic PRIVATE
)