add_library(Graphic
    SpriteVisitor.cc
    Renderers/MapRenderer.cc
)

target_include_directories(Graphic PUBLIC
    SFML::Graphic
    ${CMAKE_SOURCE_DIR}/include/Artifacts
    ${CMAKE_SOURCE_DIR}/include/Graphic
    ${CMAKE_SOURCE_DIR}/include/WorldMap
    ${CMAKE_SOURCE_DIR}/include/Battle
    ${CMAKE_SOURCE_DIR}/include/
)

target_link_libraries(Graphic PRIVATE
    SFML::Graphics SFML::Window SFML::System
    Battle Artifacts WorldMap)