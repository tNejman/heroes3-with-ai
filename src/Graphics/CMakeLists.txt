add_library(Graphics SHARED
    SpriteVisitor.cc
    
    Renderers/GameRenderer.cc
    Renderers/MapRenderer.cc
)

target_include_directories(Graphics PRIVATE
)

target_link_libraries(Graphics PUBLIC
    SFML::Graphics
)

target_link_libraries(Graphics PRIVATE
    SFML::Window
    SFML::System
    Artifact
    WorldMap
)