f_add_test_executable(testGridTile testGridTile.cc)
target_link_libraries(testGridTile PRIVATE
    WorldMap
)

f_add_test_executable(testWorldMap testWorldMap.cc) 
target_link_libraries(testWorldMap PRIVATE
    WorldMap
)
