f_add_test_executable(testWorldMap testGridTile.cc)
target_link_libraries(testWorldMap PRIVATE
    WorldMap
)