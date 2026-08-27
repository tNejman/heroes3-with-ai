add_library(IO SHARED
    InputHandler.cc
    KeyHandler.cc
    MouseHandler.cc
)

target_include_directories(IO PRIVATE
)

target_link_libraries(IO PRIVATE 
    SFML::Graphics
)