add_library(Algorithms SHARED
    IAlgorithm.cc
    MinimaxAI.cc
)

target_include_directories(Algorithms PRIVATE
)

target_link_libraries(Algorithms PRIVATE 
    Battle
)