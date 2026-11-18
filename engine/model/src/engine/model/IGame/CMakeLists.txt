add_library(IGame SHARED
  IGame.cc
  StateStack.cc
)

target_include_directories(IGame PRIVATE
)

target_link_libraries(IGame PRIVATE
  Character
)
