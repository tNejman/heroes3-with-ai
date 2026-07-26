f_add_test_executable(testArtifact testArtifact.cc)
target_link_libraries(testArtifact PRIVATE
    Artifact
)
