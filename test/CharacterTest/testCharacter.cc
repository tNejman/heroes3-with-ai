#include <gtest/gtest.h>

#include "core/Artifact/Artifact.h"
#include "core/Artifact/ArtifactLib.h"
#include "core/Character/Builder.h"
#include "core/Character/Character.h"
#include "core/Character/Stats.h"
#include "core/Exceptions/InvalidArtifactTypeException.hpp"
#include "core/Exceptions/NotEmptySlotException.hpp"
#include "core/Unit/Faction.hpp"
#include "engine/IGame/Coords.h"

TEST( CharacterTest, createValidCharacter ) {
  // std::unique_ptr<Character> character1 = std::make_unique<Character>(
  //     "John", { 0, 0 }, character::Stats{ character::Stats::PrimarySkills{ 1, 2, 3, 4 } }, character::Stats::Misc{ 1,
  //     2 }
  //     );
  Character character1 =
      character::Builder{}
          .setName( "John" )
          .setCoords( { 0, 0 } )
          .setStats( character::Stats{
              character::Stats::PrimarySkills{ .attack_ = 1, .defense_ = 2, .power_ = 3, .knowledge_ = 4 },
              character::Stats::Misc{ .morale_ = 5, .luck_ = 6 } } )
          .build();

  ASSERT_EQ( character1.getName(), "John" );
  ASSERT_EQ( character1.getCoords(), CoordPair( 0, 0 ) );
  ASSERT_EQ( character1.stats().getPrimarySkills().attack_, 1 );
  ASSERT_EQ( character1.stats().getPrimarySkills().defense_, 2 );
  ASSERT_EQ( character1.stats().getPrimarySkills().power_, 3 );
  ASSERT_EQ( character1.stats().getPrimarySkills().knowledge_, 4 );
  ASSERT_EQ( character1.stats().getLevel().level_, 1 );
  ASSERT_EQ( character1.stats().getLevel().experience_, 0 );
  // ASSERT_EQ( character1.getStats().getMana().max_mana_, 5 );
  // ASSERT_EQ( character1.getStats().getMana().current_mana_, 5 );
  // ASSERT_EQ(character1->getMovementPoints(), );
  ASSERT_EQ( character1.stats().getMisc().morale_, 5 );
  ASSERT_EQ( character1.stats().getMisc().luck_, 6 );

  // ASSERT_FALSE( character1->getIfBackpackFull() );
}

TEST( CharacterTest, moveArtifactsAround ) {
  // std::unique_ptr<Character> character1 =
  //     std::make_unique<Character>( "John", CoordPair( 0u, 0u ), 1, 2, 3, 4, 5, 6, 7 );
  Character character1 =
      character::Builder{}
          .setName( "John" )
          .setCoords( { 0, 0 } )
          .setStats( character::Stats{
              character::Stats::PrimarySkills{ .attack_ = 1, .defense_ = 2, .power_ = 3, .knowledge_ = 4 },
              character::Stats::Misc{ .morale_ = 5, .luck_ = 6 } } )
          .build();
  Artifact crown_otsm = Artifact::create( artifact::Type::CROWN_OF_THE_SUPREME_MAGI );

  character1.inventory().pickUpArtifact( crown_otsm );
  ASSERT_EQ( character1.inventory().getBackpack().size(), 1 );
  ASSERT_EQ( character1.inventory().getBackpack()[0].getData().type_, artifact::Type::CROWN_OF_THE_SUPREME_MAGI );

  character1.inventory().equipArtifact( artifact::Type::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET );
  ASSERT_EQ( character1.inventory().getBackpack().size(), 0 );
}

TEST( CharacterTest, equipUknownArtifact ) {
  // std::unique_ptr<Character> character1 = std::make_unique<Character>( "John", CoordPair( 0, 0 ), 1, 2, 3, 4, 5, 6, 7
  // );
  Character character1 =
      character::Builder{}
          .setName( "John" )
          .setCoords( { 0, 0 } )
          .setStats( character::Stats{
              character::Stats::PrimarySkills{ .attack_ = 1, .defense_ = 2, .power_ = 3, .knowledge_ = 4 },
              character::Stats::Misc{ .morale_ = 5, .luck_ = 6 } } )
          .build();

  ASSERT_THROW(
      character1.inventory().equipArtifact( artifact::Type::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET ),
      InvalidArtifactTypeException );
}

TEST( CharacterTest, equipTwoArtifactsIntoTheSameSlot ) {
  // std::unique_ptr<Character> character1 = std::make_unique<Character>( "John", CoordPair( 0, 0 ), 1, 2, 3, 4, 5, 6, 7
  // );
  Character character1 =
      character::Builder{}
          .setName( "John" )
          .setCoords( { 0, 0 } )
          .setStats( character::Stats{
              character::Stats::PrimarySkills{ .attack_ = 1, .defense_ = 2, .power_ = 3, .knowledge_ = 4 },
              character::Stats::Misc{ .morale_ = 5, .luck_ = 6 } } )
          .build();

  Artifact crown_otsm1 = Artifact::create( artifact::Type::CROWN_OF_THE_SUPREME_MAGI );
  Artifact crown_otsm2 = Artifact::create( artifact::Type::CROWN_OF_THE_SUPREME_MAGI );

  character1.inventory().pickUpArtifact( crown_otsm1 );
  character1.inventory().pickUpArtifact( crown_otsm2 );

  ASSERT_NO_THROW(
      character1.inventory().equipArtifact( artifact::Type::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET ) );
  ASSERT_THROW(
      character1.inventory().equipArtifact( artifact::Type::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET ),
      NotEmptySlotException );
}

TEST( CharacterTest, copyCharacter ) {
  // std::shared_ptr<Character> character_original =
  //     std::make_shared<Character>( "John", CoordPair( 0u, 0u ), 1, 2, 3, 4, 5, 6, 7 );
  Character character_original =
      character::Builder{}
          .setName( "John" )
          .setCoords( { 0, 0 } )
          .setStats( character::Stats{
              character::Stats::PrimarySkills{ .attack_ = 1, .defense_ = 2, .power_ = 3, .knowledge_ = 4 },
              character::Stats::Misc{ .morale_ = 5, .luck_ = 6 } } )
          .build();

  auto artifact_1 = Artifact::create( artifact::Type::CROWN_OF_THE_SUPREME_MAGI );
  auto artifact_2 = Artifact::create( artifact::Type::THUNDER_HELMET );

  character_original.inventory().pickUpArtifact( artifact_1 );
  character_original.inventory().pickUpArtifact( artifact_2 );

  character_original.inventory().equipArtifact( artifact::Type::THUNDER_HELMET, EquipmentSlots::HELMET );

  // auto faction = std::make_shared<FactionCastle>();
  // auto pikeman = faction->getUnit( CastleUnitType::PIKEMAN );
  // auto pikemen_stack = std::make_shared<UnitStack>( pikeman, 30 );

  // character_original->recruitUnitStack( pikemen_stack );

  // auto character_copy = character_original->copy();

  // ASSERT_NE( character_original, character_copy );
  // ASSERT_EQ( character_original->getAttack(), character_copy->getAttack() );
  // ASSERT_EQ( character_original->getName(), character_copy->getName() );
  // ASSERT_EQ( character_original->getCoords(), character_copy->getCoords() );
  // ASSERT_EQ( character_original->getBackpack().size(), character_copy->getBackpack().size() );
  // ASSERT_EQ( character_original->getPartySize(), character_copy->getPartySize() );

  // ASSERT_EQ( character_original->getBackpack()[0].getData().type_, character_copy->getBackpack()[0].getData().type_
  // );
}