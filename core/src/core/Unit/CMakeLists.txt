add_library(Unit SHARED
    UnitStack.cc
)

target_include_directories(Unit PRIVATE
)

target_link_libraries(Unit PRIVATE
    magic_enum::magic_enum
)