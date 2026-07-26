add_library(Units
    Unit.cc
    UnitStack.cc
    RangedUnit.cc
)

target_include_directories(Units PUBLIC
    SFML::Graphic
    ${CMAKE_SOURCE_DIR}/include/
)
