#include <gtest/gtest.h>

#include "core/Artifact/Artifact.h"
#include "core/Artifact/ArtifactLib.h"
#include "core/Misc/ProjectLib.h"

TEST( ArtifactTest, createValidArtifact ) {
  const auto crown_of_the_supreme_magi = Artifact::create( artifact::Type::CROWN_OF_THE_SUPREME_MAGI );
  const auto& crown_data = crown_of_the_supreme_magi.getData();

  EXPECT_EQ( crown_data.type_, artifact::Type::CROWN_OF_THE_SUPREME_MAGI );
  EXPECT_EQ( crown_data.slot_, EquipmentSlots::HELMET );
  EXPECT_EQ( crown_data.attack_, 0 );
  EXPECT_EQ( crown_data.defense_, 0 );
  EXPECT_EQ( crown_data.power_, 5 );
  EXPECT_EQ( crown_data.knowledge_, 5 );
  EXPECT_EQ( crown_data.speed_, 0 );
  EXPECT_EQ( crown_data.cost_, 10'000U );
}

TEST( ArtifactTest, copyArtifact ) {
  const auto artifact = Artifact::create( artifact::Type::THUNDER_HELMET );
  const auto artifact_copy = artifact.copy();

  EXPECT_EQ( artifact, artifact_copy );
  EXPECT_EQ( artifact.getData(), artifact_copy.getData() );
}
