add_library(Algorithms
    MinimaxAI.cc
)

target_include_directories(Algorithms PUBLIC
    SFML::Graphic
    ${CMAKE_SOURCE_DIR}/include/Algorithms
    ${CMAKE_SOURCE_DIR}/include/Miscellaneous
    ${CMAKE_SOURCE_DIR}/include/Battle/Moves
    ${CMAKE_SOURCE_DIR}/include/
)
target_link_libraries(Algorithms PRIVATE Battle)