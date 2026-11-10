f_add_test_executable(testCoords testCoords.cc)
target_link_libraries(testCoords PRIVATE
    Coords
    magic_enum::magic_enum
)