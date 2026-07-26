add_library(Artifacts
    Artifact.cc
)

target_include_directories(Artifacts PUBLIC
    SFML::Graphic
    ${CMAKE_SOURCE_DIR}/include/Artifacts
    ${CMAKE_SOURCE_DIR}/include/Miscellaneous
    ${CMAKE_SOURCE_DIR}/include/
)

target_link_libraries(Artifacts PRIVATE Miscellaneous)