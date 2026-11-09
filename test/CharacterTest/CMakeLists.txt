f_add_test_executable(testCharacter testCharacter.cc)
target_compile_options(testCharacter PRIVATE -freflection)
target_link_libraries(testCharacter PRIVATE
    Character
    WorldMap
)