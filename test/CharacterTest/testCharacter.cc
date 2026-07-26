#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include "Artifact/Artifact.h"
#include "Character/Character.h"
#include "Exceptions/InvalidArtifactTypeException.hpp"
#include "Exceptions/NotEmptySlotException.hpp"
#include "Miscellaneous/ArtifactLib.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "Miscellaneous/UnitsLib.h"
#include "Unit/Faction.hpp"
#include "Unit/UnitStack.h"

TEST( CharacterTest, createValidCharacter ) {
  std::unique_ptr<Character> character1 =
      std::make_unique<Character>( "John", CoordPair( 0u, 0u ), 1, 2, 3, 4, 5, 6, 7 );
  ASSERT_EQ( character1->getName(), "John" );
  ASSERT_TRUE( character1->getIfAlive() );
  ASSERT_EQ( character1->getCoords(), CoordPair( 0u, 0u ) );
  ASSERT_EQ( character1->getAttack(), 1 );
  ASSERT_EQ( character1->getDefense(), 2 );
  ASSERT_EQ( character1->getPower(), 3 );
  ASSERT_EQ( character1->getKnowledge(), 4 );
  ASSERT_EQ( character1->getLevel(), 1 );
  ASSERT_EQ( character1->getExperience(), 0 );
  ASSERT_EQ( character1->getMaxMana(), 5 );
  ASSERT_EQ( character1->getCurrentMana(), 5 );
  // ASSERT_EQ(character1->getMovementPoints(), );
  ASSERT_EQ( character1->getMorale(), 6 );
  ASSERT_EQ( character1->getLuck(), 7 );

  ASSERT_FALSE( character1->getIfBackpackFull() );
}

TEST( CharacterTest, moveArtifactsAround ) {
  std::unique_ptr<Character> character1 =
      std::make_unique<Character>( "John", CoordPair( 0u, 0u ), 1, 2, 3, 4, 5, 6, 7 );
  std::unique_ptr<Artifact> crown_otsm = Artifact::create( ArtifactType::CROWN_OF_THE_SUPREME_MAGI );

  character1->pickUpArtifact( std::move( crown_otsm ) );
  ASSERT_EQ( crown_otsm, nullptr );
  ASSERT_EQ( character1->getBackpack().size(), 1 );
  ASSERT_EQ( character1->getBackpack()[0]->getType(), ArtifactType::CROWN_OF_THE_SUPREME_MAGI );

  character1->equipArtifact( ArtifactType::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET );
  ASSERT_EQ( character1->getBackpack().size(), 0 );
}

TEST( CharacterTest, equipUknownArtifact ) {
  std::unique_ptr<Character> character1 =
      std::make_unique<Character>( "John", CoordPair( 0u, 0u ), 1, 2, 3, 4, 5, 6, 7 );

  ASSERT_THROW( character1->equipArtifact( ArtifactType::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET ),
                InvalidArtifactTypeException );
}

TEST( CharacterTest, equipTwoArtifactsIntoTheSameSlot ) {
  std::unique_ptr<Character> character1 =
      std::make_unique<Character>( "John", CoordPair( 0u, 0u ), 1, 2, 3, 4, 5, 6, 7 );
  std::unique_ptr<Artifact> crown_otsm1 = Artifact::create( ArtifactType::CROWN_OF_THE_SUPREME_MAGI );
  std::unique_ptr<Artifact> crown_otsm2 = Artifact::create( ArtifactType::CROWN_OF_THE_SUPREME_MAGI );

  character1->pickUpArtifact( std::move( crown_otsm1 ) );
  character1->pickUpArtifact( std::move( crown_otsm2 ) );

  ASSERT_NO_THROW( character1->equipArtifact( ArtifactType::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET ) );
  ASSERT_THROW( character1->equipArtifact( ArtifactType::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET ),
                NotEmptySlotException );
}

TEST( CharacterTest, copyCharacter ) {
  std::shared_ptr<Character> character_original =
      std::make_shared<Character>( "John", CoordPair( 0u, 0u ), 1, 2, 3, 4, 5, 6, 7 );

  auto artifact_1 = Artifact::create( ArtifactType::CROWN_OF_THE_SUPREME_MAGI );
  auto artifact_2 = Artifact::create( ArtifactType::THUNDER_HELMET );

  character_original->pickUpArtifact( std::move( artifact_1 ) );
  character_original->pickUpArtifact( std::move( artifact_2 ) );

  character_original->equipArtifact( ArtifactType::THUNDER_HELMET, EquipmentSlots::HELMET );

  auto faction = std::make_shared<FactionCastle>();
  auto pikeman = faction->getUnit( CastleUnitType::PIKEMAN );
  auto pikemen_stack = std::make_shared<UnitStack>( pikeman, 30 );

  character_original->recruitUnitStack( pikemen_stack );

  auto character_copy = character_original->copy();

  ASSERT_NE( character_original, character_copy );
  ASSERT_EQ( character_original->getAttack(), character_copy->getAttack() );
  ASSERT_EQ( character_original->getName(), character_copy->getName() );
  ASSERT_EQ( character_original->getCoords(), character_copy->getCoords() );
  ASSERT_EQ( character_original->getBackpack().size(), character_copy->getBackpack().size() );
  ASSERT_EQ( character_original->getPartySize(), character_copy->getPartySize() );

  ASSERT_EQ( character_original->getBackpack()[0]->getType(), character_copy->getBackpack()[0]->getType() );
}