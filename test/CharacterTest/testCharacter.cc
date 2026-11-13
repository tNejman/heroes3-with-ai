#include <gtest/gtest.h>

#include <memory>

#include "aux/Builder.hpp"
#include "core/Artifact/Artifact.h"
#include "core/Artifact/ArtifactLib.h"
#include "core/Character/Character.h"
#include "core/Character/Stats.h"
#include "core/Exceptions/InvalidArtifactTypeException.hpp"
#include "core/Exceptions/NotEmptySlotException.hpp"
#include "core/Misc/BuilderDefaults.hpp"
#include "engine/model/IGame/Coords.h"

namespace {

Character makeJohn() {
  return Builder<Character>{}
      .setName( "John" )
      .setCoords( CoordPair{ 3, 4 } )
      .setStats( Builder<character::Stats>{}
                     .setPrimarySkills(
                         character::Stats::PrimarySkills{ .attack_ = 1, .defense_ = 2, .power_ = 3, .knowledge_ = 4 } )
                     .setMisc( character::Stats::Misc{ .morale_ = 5, .luck_ = 6 } )
                     .build() )
      .build();
}

void expectSameStats( const character::Stats& actual, const character::Stats& expected ) {
  EXPECT_EQ( actual.getPrimarySkills().attack_, expected.getPrimarySkills().attack_ );
  EXPECT_EQ( actual.getPrimarySkills().defense_, expected.getPrimarySkills().defense_ );
  EXPECT_EQ( actual.getPrimarySkills().power_, expected.getPrimarySkills().power_ );
  EXPECT_EQ( actual.getPrimarySkills().knowledge_, expected.getPrimarySkills().knowledge_ );
  EXPECT_EQ( actual.getLevel().level_, expected.getLevel().level_ );
  EXPECT_EQ( actual.getLevel().experience_, expected.getLevel().experience_ );
  EXPECT_EQ( actual.getMisc().morale_, expected.getMisc().morale_ );
  EXPECT_EQ( actual.getMisc().luck_, expected.getMisc().luck_ );
}

}  // namespace

TEST( CharacterTest, createValidCharacter ) {
  const Character john = makeJohn();

  EXPECT_EQ( john.getName(), "John" );
  EXPECT_EQ( john.getCoords(), CoordPair( 3, 4 ) );
  EXPECT_EQ( john.stats().getPrimarySkills().attack_, 1 );
  EXPECT_EQ( john.stats().getPrimarySkills().defense_, 2 );
  EXPECT_EQ( john.stats().getPrimarySkills().power_, 3 );
  EXPECT_EQ( john.stats().getPrimarySkills().knowledge_, 4 );
  EXPECT_EQ( john.stats().getLevel().level_, 1 );
  EXPECT_EQ( john.stats().getLevel().experience_, 0 );
  EXPECT_EQ( john.stats().getMisc().morale_, 5 );
  EXPECT_EQ( john.stats().getMisc().luck_, 6 );
}

TEST( CharacterTest, equipArtifactMovesItFromBackpackToSlot ) {
  Character character = Builder<Character>{}.build();

  character.inventory().pickUpArtifact( Artifact::create( artifact::Type::CROWN_OF_THE_SUPREME_MAGI ) );
  ASSERT_EQ( character.inventory().getBackpack().size(), 1 );
  EXPECT_EQ( character.inventory().getBackpack()[0].getData().type_, artifact::Type::CROWN_OF_THE_SUPREME_MAGI );

  character.inventory().equipArtifact( artifact::Type::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET );

  EXPECT_TRUE( character.inventory().getBackpack().empty() );
  const auto& helmet = character.inventory().getSlot( EquipmentSlots::HELMET );
  ASSERT_TRUE( helmet.has_value() );
  EXPECT_EQ( helmet->getData().type_, artifact::Type::CROWN_OF_THE_SUPREME_MAGI );
}

TEST( CharacterTest, equipArtifactNotInBackpackThrows ) {
  Character character = Builder<Character>{}.build();

  EXPECT_THROW(
      character.inventory().equipArtifact( artifact::Type::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET ),
      InvalidArtifactTypeException );
}

TEST( CharacterTest, equipTwoArtifactsIntoTheSameSlotThrows ) {
  Character character = Builder<Character>{}.build();
  character.inventory().pickUpArtifact( Artifact::create( artifact::Type::CROWN_OF_THE_SUPREME_MAGI ) );
  character.inventory().pickUpArtifact( Artifact::create( artifact::Type::CROWN_OF_THE_SUPREME_MAGI ) );

  ASSERT_NO_THROW(
      character.inventory().equipArtifact( artifact::Type::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET ) );
  EXPECT_THROW(
      character.inventory().equipArtifact( artifact::Type::CROWN_OF_THE_SUPREME_MAGI, EquipmentSlots::HELMET ),
      NotEmptySlotException );
}

TEST( CharacterTest, copyCharacter ) {
  Character original = makeJohn();
  original.inventory().pickUpArtifact( Artifact::create( artifact::Type::CROWN_OF_THE_SUPREME_MAGI ) );
  original.inventory().pickUpArtifact( Artifact::create( artifact::Type::THUNDER_HELMET ) );
  original.inventory().equipArtifact( artifact::Type::THUNDER_HELMET, EquipmentSlots::HELMET );

  const std::shared_ptr<Character> copy = original.copy();

  ASSERT_NE( copy, nullptr );
  EXPECT_NE( copy.get(), &original );
  EXPECT_EQ( copy->getId(), original.getId() );
  EXPECT_EQ( copy->getName(), original.getName() );
  EXPECT_EQ( copy->getCoords(), original.getCoords() );
  expectSameStats( copy->stats(), original.stats() );

  ASSERT_EQ( copy->inventory().getBackpack().size(), 1 );
  EXPECT_EQ( copy->inventory().getBackpack()[0].getData().type_, artifact::Type::CROWN_OF_THE_SUPREME_MAGI );
  const auto& helmet = copy->inventory().getSlot( EquipmentSlots::HELMET );
  ASSERT_TRUE( helmet.has_value() );
  EXPECT_EQ( helmet->getData().type_, artifact::Type::THUNDER_HELMET );
}

TEST( CharacterTest, copyIsIndependentOfOriginal ) {
  Character original = makeJohn();
  const std::shared_ptr<Character> copy = original.copy();

  original.inventory().pickUpArtifact( Artifact::create( artifact::Type::THUNDER_HELMET ) );

  EXPECT_EQ( original.inventory().getBackpack().size(), 1 );
  EXPECT_TRUE( copy->inventory().getBackpack().empty() );
}
