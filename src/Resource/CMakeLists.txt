add_library(Resource
    Resource.cc
)

target_include_directories(Resource PUBLIC
    SFML::Graphic
    ${CMAKE_SOURCE_DIR}/include/Resource
    ${CMAKE_SOURCE_DIR}/include/
)
