add_library(Input SHARED
    InputHandler.cc
    KeyHandler.cc
    MouseHandler.cc
)

target_include_directories(Input PRIVATE
)

target_link_libraries(Input PRIVATE 
    SFML::Graphics
)