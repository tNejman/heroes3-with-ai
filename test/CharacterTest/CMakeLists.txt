f_add_test_executable(testCharacter testCharacter.cc)
target_link_libraries(testCharacter PRIVATE
    Characters
)