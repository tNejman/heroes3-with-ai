add_library(Player
    Player.cc
)

target_include_directories(Player PUBLIC
    SFML::Graphic
    ${CMAKE_SOURCE_DIR}/include/Player
    ${CMAKE_SOURCE_DIR}/include/
)