add_library(Player SHARED
    Player.cc
)

target_include_directories(Player PRIVATE
)

target_link_libraries(Player PRIVATE
    SFML::Graphics
)