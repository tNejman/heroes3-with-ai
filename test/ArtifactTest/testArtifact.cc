#include <gtest/gtest.h>

#include "Artifacts/Artifact.h"

TEST( ArtifactTest, createValidArtifact ) {
  std::unique_ptr<Artifact> crown_of_the_supreme_magi = Artifact::create( ArtifactType::CROWN_OF_THE_SUPREME_MAGI );
  ASSERT_EQ( crown_of_the_supreme_magi->getAttack(), 0 );
  ASSERT_EQ( crown_of_the_supreme_magi->getDefense(), 0 );
  ASSERT_EQ( crown_of_the_supreme_magi->getPower(), 5 );
  ASSERT_EQ( crown_of_the_supreme_magi->getKnowledge(), 5 );
  ASSERT_EQ( crown_of_the_supreme_magi->getSpeed(), 0 );
  ASSERT_EQ( crown_of_the_supreme_magi->getCost(), 10'000u );
  ASSERT_EQ( crown_of_the_supreme_magi->getType(), ArtifactType::CROWN_OF_THE_SUPREME_MAGI );
  ASSERT_EQ( crown_of_the_supreme_magi->getSlot(), EquipmentSlots::HELMET );
}

TEST( ArtifactTest, copyArtifact ) {
  auto artifact = Artifact::create( ArtifactType::THUNDER_HELMET );
  auto artifact_copy = artifact->copy();

  ASSERT_NE( artifact, artifact_copy );
  ASSERT_EQ( artifact->getType(), artifact_copy->getType() );
  ASSERT_EQ( artifact->getSlot(), artifact_copy->getSlot() );
  ASSERT_EQ( artifact->getName(), artifact_copy->getName() );
  ASSERT_EQ( artifact->getAttack(), artifact_copy->getAttack() );
  ASSERT_EQ( artifact->getPower(), artifact_copy->getPower() );
  ASSERT_EQ( artifact->getKnowledge(), artifact_copy->getKnowledge() );
  ASSERT_EQ( artifact->getSpeed(), artifact_copy->getSpeed() );
  ASSERT_EQ( artifact->getCost(), artifact_copy->getCost() );
}