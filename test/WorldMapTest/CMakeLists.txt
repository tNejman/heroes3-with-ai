f_add_test_executable(testWorldMap testWorldMap.cc) 
target_link_libraries(testWorldMap PRIVATE
    WorldMap
    Unit
)
