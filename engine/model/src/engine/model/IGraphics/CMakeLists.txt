add_library(IGraphics SHARED
    TextureLoader.cc
)

target_include_directories(IGraphics PRIVATE
)

target_link_libraries(IGraphics PUBLIC
    SFML::Graphics
)