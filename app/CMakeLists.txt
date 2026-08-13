add_executable(${APP_NAME} Main.cc)
apply_compiler_flags(${APP_NAME})
target_include_directories(${APP_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${APP_NAME} PRIVATE
    ${MODULES}
    SFML::Graphics
)

add_executable(MainBackup Main2.cc)
apply_compiler_flags(MainBackup)
target_include_directories(MainBackup PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(MainBackup PRIVATE
    ${MODULES}
    SFML::Graphics
)