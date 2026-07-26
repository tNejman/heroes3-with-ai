include(GoogleTest)

# Define the test executable
add_executable(testGoogleBattlefield battle/testBattlefield.cc ${PROJECT_SOURCES})
add_executable(testGoogleBattle battle/testBattle.cc ${PROJECT_SOURCES})
add_executable(testGoogleArtifact testArtifact.cc ${PROJECT_SOURCES})
add_executable(testGoogleCharacter testCharacter.cc ${PROJECT_SOURCES})

set(MODULES
    testGoogleBattlefield
    testGoogleBattle
    testGoogleArtifact
    testGoogleCharacter
)

# Link GoogleTest to the test executable
foreach(module ${MODULES})
    target_link_libraries(${module} PUBLIC
        GTest::gtest_main
        pthread
        sfml-system
        Battle Units Miscellaneous)

    target_include_directories(${module} PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/include/Artifact/
        ${CMAKE_SOURCE_DIR}/include/Battle/
        ${CMAKE_SOURCE_DIR}/include/Character/
        ${CMAKE_SOURCE_DIR}/include/Miscellaneous/
    )

    gtest_discover_tests(${module})
endforeach()