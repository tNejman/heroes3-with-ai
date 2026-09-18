add_library(Coords SHARED
    Coords.cc
)

target_include_directories(Coords PRIVATE
)

target_link_libraries(Coords PRIVATE 
)

# ===== =====

add_library(IGame SHARED
    IGame.cc
    StateStack.cc
)

target_include_directories(IGame PRIVATE
)

target_link_libraries(IGame PRIVATE 
)