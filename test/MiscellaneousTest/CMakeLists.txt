f_add_test_executable(testMiscellaneous testCoords.cc)
target_link_libraries(testMiscellaneous PRIVATE
    Miscellaneous
)