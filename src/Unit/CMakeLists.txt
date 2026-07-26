add_library(Unit SHARED
    Unit.cc
    UnitStack.cc
    RangedUnit.cc
)

target_include_directories(Unit PRIVATE
)

target_link_libraries(Unit PRIVATE
    SFML::Graphics
)