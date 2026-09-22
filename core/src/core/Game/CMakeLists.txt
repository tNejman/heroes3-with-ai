add_library(Game SHARED
    Context.cc
    Game.cc
    StateBattle.cc
    StateOverworld.cc
)

target_include_directories(Game PRIVATE
)

target_link_libraries(Game PUBLIC
    Coords
    magic_enum::magic_enum
)
