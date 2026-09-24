#include <gtest/gtest.h>

#include "core/Artifact/Artifact.h"
#include "core/Artifact/ArtifactLib.h"
#include "core/Misc/ProjectLib.h"

TEST( ArtifactTest, createValidArtifact ) {
  auto crown_of_the_supreme_magi = Artifact::create( artifact::Type::CROWN_OF_THE_SUPREME_MAGI );
  const auto& crown_data = crown_of_the_supreme_magi.getData();
  ASSERT_EQ( crown_data.attack_, 0 );
  ASSERT_EQ( crown_data.defense_, 0 );
  ASSERT_EQ( crown_data.power_, 5 );
  ASSERT_EQ( crown_data.knowledge_, 5 );
  ASSERT_EQ( crown_data.speed_, 0 );
  ASSERT_EQ( crown_data.cost_, 10'000U );
  ASSERT_EQ( crown_data.type_, artifact::Type::CROWN_OF_THE_SUPREME_MAGI );
  ASSERT_EQ( crown_data.slot_, EquipmentSlots::HELMET );
}

TEST( ArtifactTest, copyArtifact ) {
  auto artifact = Artifact::create( artifact::Type::THUNDER_HELMET );
  auto artifact_copy = artifact.copy();

  ASSERT_EQ( artifact.getData(), artifact_copy.getData() );
}