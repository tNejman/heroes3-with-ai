#include <gtest/gtest.h>

#include <ostream>

#include "engine/model/IGame/Coords.h"

// Lets gtest print ShiftPair values in failure messages (CoordPair already has operator<<).
// Must stay in ShiftPair's (global) namespace for ADL, hence `static` rather than an anonymous namespace.
static void PrintTo( const ShiftPair& shift, std::ostream* os ) {
  *os << "ShiftPair{" << shift.dx_ << ", " << shift.dy_ << "}";
}

// Operands below are `const` on purpose: if an operator ever stopped taking its operands by const
// reference, these tests would fail to compile instead of needing "operand unchanged" assertions.

/*
====== Shift Pair ======
*/

TEST( ShiftPairTest, constructorStoresComponents ) {
  const ShiftPair shift( 10, -11 );

  EXPECT_EQ( shift.dx_, 10 );
  EXPECT_EQ( shift.dy_, -11 );
}

TEST( ShiftPairTest, copyPreservesComponents ) {
  const ShiftPair original( 10, 11 );
  const ShiftPair copy = original;  // NOLINT(performance-unnecessary-copy-initialization)

  EXPECT_EQ( copy, original );
  EXPECT_EQ( copy, ShiftPair( 10, 11 ) );
}

TEST( ShiftPairTest, operatorPlus ) {
  const ShiftPair left_op( 10, 11 );
  const ShiftPair right_op( 5, 7 );

  EXPECT_EQ( left_op + right_op, ShiftPair( 15, 18 ) );
}

TEST( ShiftPairTest, operatorMinus ) {
  const ShiftPair left_op( 10, 11 );
  const ShiftPair right_op( 5, 7 );

  EXPECT_EQ( left_op - right_op, ShiftPair( 5, 4 ) );
}

TEST( ShiftPairTest, equality ) {
  const ShiftPair shift_pair1( 10, 11 );
  const ShiftPair shift_pair2( 5, 7 );
  const ShiftPair shift_pair3( 10, 11 );

  EXPECT_FALSE( shift_pair1 == shift_pair2 );
  EXPECT_TRUE( shift_pair1 == shift_pair3 );
  EXPECT_TRUE( shift_pair1 != shift_pair2 );
  EXPECT_FALSE( shift_pair1 != shift_pair3 );
}

/*
====== Coord Pair ======
*/

namespace {
template <typename T>
class CoordPairConstructorTest : public ::testing::Test {};
}  // namespace

using IntegralTypes = ::testing::Types<short, int, long, long long, unsigned, unsigned long>;
TYPED_TEST_SUITE( CoordPairConstructorTest, IntegralTypes );

TYPED_TEST( CoordPairConstructorTest, acceptsAnyIntegralType ) {
  const CoordPair coords( TypeParam{ 10 }, TypeParam{ 12 } );

  EXPECT_EQ( coords.x_, 10 );
  EXPECT_EQ( coords.y_, 12 );
}

TEST( CoordPairTest, copyPreservesComponents ) {
  const CoordPair original( 10, 15 );
  const CoordPair copy = original;  // NOLINT(performance-unnecessary-copy-initialization)

  EXPECT_EQ( copy, original );
  EXPECT_EQ( copy, CoordPair( 10, 15 ) );
}

TEST( CoordPairTest, operatorPlusCoordPair ) {
  const CoordPair left_op( 10, 15 );
  const CoordPair right_op( 5, 7 );

  EXPECT_EQ( left_op + right_op, CoordPair( 15, 22 ) );
}

TEST( CoordPairTest, operatorPlusShiftPair ) {
  const CoordPair left_op( 10, 15 );
  const ShiftPair right_op( 5, 7 );

  EXPECT_EQ( left_op + right_op, CoordPair( 15, 22 ) );
}

TEST( CoordPairTest, operatorMinus ) {
  const CoordPair left_op( 10, 15 );
  const CoordPair right_op( 5, 7 );

  EXPECT_EQ( left_op - right_op, CoordPair( 5, 8 ) );
}

TEST( CoordPairTest, operatorPlusEqualsCoordPair ) {
  CoordPair left_op( 10, 15 );
  const CoordPair right_op( 5, 7 );

  left_op += right_op;

  EXPECT_EQ( left_op, CoordPair( 15, 22 ) );
}

TEST( CoordPairTest, operatorPlusEqualsShiftPair ) {
  CoordPair left_op( 10, 15 );
  const ShiftPair right_op( 5, 7 );

  left_op += right_op;

  EXPECT_EQ( left_op, CoordPair( 15, 22 ) );
}

TEST( CoordPairTest, equality ) {
  const CoordPair coord_pair1( 10, 15 );
  const CoordPair coord_pair2( 5, 7 );
  const CoordPair coord_pair3( 10, 15 );

  EXPECT_FALSE( coord_pair1 == coord_pair2 );
  EXPECT_TRUE( coord_pair1 == coord_pair3 );
  EXPECT_TRUE( coord_pair1 != coord_pair2 );
  EXPECT_FALSE( coord_pair1 != coord_pair3 );
}

TEST( CoordPairTest, orderingComparesXFirstThenY ) {
  const CoordPair smaller( 5, 7 );
  const CoordPair larger( 10, 15 );
  const CoordPair larger_copy( 10, 15 );
  const CoordPair same_x_larger_y( 10, 16 );
  const CoordPair larger_x_smaller_y( 11, 0 );

  EXPECT_LT( smaller, larger );
  EXPECT_LE( smaller, larger );
  EXPECT_GT( larger, smaller );
  EXPECT_GE( larger, smaller );

  EXPECT_FALSE( larger < larger_copy );
  EXPECT_LE( larger, larger_copy );
  EXPECT_FALSE( larger > larger_copy );
  EXPECT_GE( larger, larger_copy );

  EXPECT_LT( larger, same_x_larger_y );
  EXPECT_LT( larger, larger_x_smaller_y );
}

TEST( CoordPairTest, distanceFrom ) {
  const CoordPair coord_pair1( 10, 15 );
  const CoordPair coord_pair2( 7, 11 );

  EXPECT_DOUBLE_EQ( coord_pair1.distanceFrom( coord_pair2 ), 5.0 );
  EXPECT_DOUBLE_EQ( coord_pair2.distanceFrom( coord_pair1 ), 5.0 );
  EXPECT_DOUBLE_EQ( coord_pair1.distanceFrom( coord_pair1 ), 0.0 );
}
