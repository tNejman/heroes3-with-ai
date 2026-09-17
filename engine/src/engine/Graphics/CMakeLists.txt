add_library(Graphics SHARED
    SpriteFactory.cc
    SpriteVisitor.cc
    
    Renderers/BattleRenderer.cc
    Renderers/GameRenderer.cc
    Renderers/MapRenderer.cc
)

target_include_directories(Graphics PRIVATE
)

target_link_libraries(Graphics PUBLIC
    SFML::Graphics
    magic_enum::magic_enum
)

target_link_libraries(Graphics PRIVATE
    SFML::Window
    SFML::System
    Artifact
    WorldMap
)