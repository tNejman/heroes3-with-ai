add_library(Character SHARED
  Character.cc
  Army.cc
  Builder.cc
  Inventory.cc
  Stats.cc
)

target_include_directories(Character PRIVATE
)

target_link_libraries(Character PUBLIC
  Artifact
  Coords
  Unit
  Magic
  MapObject
)
