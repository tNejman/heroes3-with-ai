#include <gtest/gtest.h>

#include "Exceptions/CoordinateOutOfBoundsException.hpp"
#include "Miscellaneous/Coords.h"

/*
====== Shift Pair ======
*/

// NOLINTBEGIN(-Wunused-value)

TEST( ShiftPairTest, constructorParametrized ) {
  //   ASSERT_NO_THROW( ShiftPair( 10, 10 ) );
  ASSERT_NO_THROW( ShiftPair( 10U, 10U ) );
  ASSERT_NO_THROW( ShiftPair( (int)10, (int)10 ) );
  ASSERT_NO_THROW( ShiftPair( (short)10, (short)10 ) );
  ASSERT_NO_THROW( ShiftPair( (long)10, (long)10 ) );
  ASSERT_NO_THROW( ShiftPair( (long long)10, (long long)10 ) );
}

TEST( ShiftPairTest, constructorCopy ) {
  ShiftPair shift_pair( 10, 11 );
  ASSERT_NO_THROW( ShiftPair shift_pair_copy( shift_pair ) );
  ASSERT_NO_THROW( ShiftPair shift_pair_copy2( ShiftPair( 10, 11 ) ) );
}

TEST( ShiftPairTest, operatorEquals ) {
  ShiftPair shift_pair1( 10, 11 );
  ShiftPair shift_pair2 = shift_pair1;

  // check if original was modified
  ASSERT_EQ( shift_pair1.dx_, 10 );
  ASSERT_EQ( shift_pair1.dy_, 11 );

  // check if result is the same
  ASSERT_EQ( shift_pair2.dx_, 10 );
  ASSERT_EQ( shift_pair2.dy_, 11 );
}

TEST( ShiftPairTest, operatorPlus ) {
  ShiftPair left_op( 10, 11 );
  ShiftPair right_op( 5, 7 );
  ShiftPair result = left_op + right_op;
  // check if operands were modified
  ASSERT_EQ( left_op.dx_, 10 );
  ASSERT_EQ( left_op.dy_, 11 );
  ASSERT_EQ( right_op.dx_, 5 );
  ASSERT_EQ( right_op.dy_, 7 );

  // check if result is correct
  ASSERT_EQ( result.dx_, 15 );
  ASSERT_EQ( result.dy_, 18 );
}

TEST( ShiftPairTest, operatorMinus ) {
  ShiftPair left_op( 10, 11 );
  ShiftPair right_op( 5, 7 );
  ShiftPair result = left_op - right_op;
  // check if operands were modified
  ASSERT_EQ( left_op.dx_, 10 );
  ASSERT_EQ( left_op.dy_, 11 );
  ASSERT_EQ( right_op.dx_, 5 );
  ASSERT_EQ( right_op.dy_, 7 );

  // check if result is correct
  ASSERT_EQ( result.dx_, 5 );
  ASSERT_EQ( result.dy_, 4 );
}

TEST( ShiftPairTest, operatorIsTheSame ) {
  ShiftPair shift_pair1( 10, 11 );
  ShiftPair shift_pair2( 5, 7 );
  ShiftPair shift_pair3( 10, 11 );

  ASSERT_FALSE( shift_pair1 == shift_pair2 );
  ASSERT_TRUE( shift_pair1 == shift_pair3 );

  // check if operands were modified
  ASSERT_EQ( shift_pair1.dx_, 10 );
  ASSERT_EQ( shift_pair1.dy_, 11 );
  ASSERT_EQ( shift_pair2.dx_, 5 );
  ASSERT_EQ( shift_pair2.dy_, 7 );
  ASSERT_EQ( shift_pair3.dx_, 10 );
  ASSERT_EQ( shift_pair3.dy_, 11 );
}

TEST( ShiftPairTest, operatorIsNotTheSame ) {
  ShiftPair shift_pair1( 10, 11 );
  ShiftPair shift_pair2( 5, 7 );
  ShiftPair shift_pair3( 10, 11 );

  ASSERT_TRUE( shift_pair1 != shift_pair2 );
  ASSERT_FALSE( shift_pair1 != shift_pair3 );

  // check if operands were modified
  ASSERT_EQ( shift_pair1.dx_, 10 );
  ASSERT_EQ( shift_pair1.dy_, 11 );
  ASSERT_EQ( shift_pair2.dx_, 5 );
  ASSERT_EQ( shift_pair2.dy_, 7 );
  ASSERT_EQ( shift_pair3.dx_, 10 );
  ASSERT_EQ( shift_pair3.dy_, 11 );
}

/*
====== Coord Pair ======
*/

TEST( CoordPairTest, constructorParametrized ) {
  ASSERT_NO_THROW( CoordPair( 10u, 10u ) );
  ASSERT_NO_THROW( CoordPair( (int)10, (int)10 ) );
  ASSERT_NO_THROW( CoordPair( (short)10, (short)10 ) );
  ASSERT_NO_THROW( CoordPair( (long)10, (long)10 ) );
  ASSERT_NO_THROW( CoordPair( (long long)10, (long long)10 ) );

  // ASSERT_ANY_THROW( CoordPair( -10, -10 ) );
  // actually compiler wouldn't let this be compiled and therefore ran
}

TEST( CoordPairTest, operatorEquals ) {
  CoordPair coord_pair( 10, 15 );
  CoordPair coord_pair2 = coord_pair;

  ASSERT_EQ( coord_pair.x_, 10 );
  ASSERT_EQ( coord_pair.y_, 15 );

  ASSERT_EQ( coord_pair2.x_, 10 );
  ASSERT_EQ( coord_pair2.y_, 15 );
}

TEST( CoordPairTest, operatorPlusCoordPair ) {
  CoordPair left_op( 10, 15 );
  CoordPair right_op( 5, 7 );
  CoordPair result = left_op + right_op;

  ASSERT_EQ( left_op.x_, 10 );
  ASSERT_EQ( left_op.y_, 15 );
  ASSERT_EQ( right_op.x_, 5 );
  ASSERT_EQ( right_op.y_, 7 );

  ASSERT_EQ( result.x_, 15 );
  ASSERT_EQ( result.y_, 22 );
}

TEST( CoordPairTest, operatorPlusShiftPair ) {
  CoordPair left_op( 10, 15 );
  ShiftPair right_op( 5, 7 );
  CoordPair result = left_op + right_op;

  ASSERT_EQ( left_op.x_, 10 );
  ASSERT_EQ( left_op.y_, 15 );
  ASSERT_EQ( right_op.dx_, 5 );
  ASSERT_EQ( right_op.dy_, 7 );

  ASSERT_EQ( result.x_, 15 );
  ASSERT_EQ( result.y_, 22 );
}

TEST( CoordPairTest, operatorMinus ) {
  CoordPair left_op( 10, 15 );
  CoordPair right_op( 5, 7 );
  CoordPair result = left_op - right_op;

  ASSERT_EQ( left_op.x_, 10 );
  ASSERT_EQ( left_op.y_, 15 );
  ASSERT_EQ( right_op.x_, 5 );
  ASSERT_EQ( right_op.y_, 7 );

  ASSERT_EQ( result.x_, 5 );
  ASSERT_EQ( result.y_, 8 );
}

TEST( CoordPairTest, operatorPlusEqualsCoordPair ) {
  CoordPair left_op( 10, 15 );
  CoordPair right_op( 5, 7 );
  left_op += right_op;

  ASSERT_EQ( left_op.x_, 15 );
  ASSERT_EQ( left_op.y_, 22 );
  ASSERT_EQ( right_op.x_, 5 );
  ASSERT_EQ( right_op.y_, 7 );
}

TEST( CoordPairTest, operatorPlusEqualsShiftPair ) {
  CoordPair left_op( 10, 15 );
  ShiftPair right_op( 5, 7 );
  left_op += right_op;

  ASSERT_EQ( left_op.x_, 15 );
  ASSERT_EQ( left_op.y_, 22 );
  ASSERT_EQ( right_op.dx_, 5 );
  ASSERT_EQ( right_op.dy_, 7 );
}

TEST( CoordPairTest, operatorIsTheSame ) {
  CoordPair coord_pair1( 10, 15 );
  CoordPair coord_pair2( 5, 7 );
  CoordPair coord_pair3( 10, 15 );

  ASSERT_FALSE( coord_pair1 == coord_pair2 );
  ASSERT_TRUE( coord_pair1 == coord_pair3 );

  ASSERT_EQ( coord_pair1.x_, 10 );
  ASSERT_EQ( coord_pair1.y_, 15 );
  ASSERT_EQ( coord_pair2.x_, 5 );
  ASSERT_EQ( coord_pair2.y_, 7 );
  ASSERT_EQ( coord_pair3.x_, 10 );
  ASSERT_EQ( coord_pair3.y_, 15 );
}

TEST( CoordPairTest, operatorIsNotTheSame ) {
  CoordPair coord_pair1( 10, 15 );
  CoordPair coord_pair2( 5, 7 );
  CoordPair coord_pair3( 10, 15 );

  ASSERT_TRUE( coord_pair1 != coord_pair2 );
  ASSERT_FALSE( coord_pair1 != coord_pair3 );

  ASSERT_EQ( coord_pair1.x_, 10 );
  ASSERT_EQ( coord_pair1.y_, 15 );
  ASSERT_EQ( coord_pair2.x_, 5 );
  ASSERT_EQ( coord_pair2.y_, 7 );
  ASSERT_EQ( coord_pair3.x_, 10 );
  ASSERT_EQ( coord_pair3.y_, 15 );
}

TEST( CoordPairTest, operatorLessThan ) {
  CoordPair coord_pair1( 10, 15 );
  CoordPair coord_pair2( 5, 7 );
  CoordPair coord_pair3( 10, 15 );

  ASSERT_TRUE( coord_pair2 < coord_pair1 );
  ASSERT_FALSE( coord_pair1 < coord_pair3 );

  ASSERT_EQ( coord_pair1.x_, 10 );
  ASSERT_EQ( coord_pair1.y_, 15 );
  ASSERT_EQ( coord_pair2.x_, 5 );
  ASSERT_EQ( coord_pair2.y_, 7 );
  ASSERT_EQ( coord_pair3.x_, 10 );
  ASSERT_EQ( coord_pair3.y_, 15 );
}

TEST( CoordPairTest, operatorLessThanOrEqual ) {
  CoordPair coord_pair1( 10, 15 );
  CoordPair coord_pair2( 5, 7 );
  CoordPair coord_pair3( 10, 15 );

  ASSERT_TRUE( coord_pair2 <= coord_pair1 );
  ASSERT_TRUE( coord_pair1 <= coord_pair3 );

  ASSERT_EQ( coord_pair1.x_, 10 );
  ASSERT_EQ( coord_pair1.y_, 15 );
  ASSERT_EQ( coord_pair2.x_, 5 );
  ASSERT_EQ( coord_pair2.y_, 7 );
  ASSERT_EQ( coord_pair3.x_, 10 );
  ASSERT_EQ( coord_pair3.y_, 15 );
}

TEST( CoordPairTest, operatorGreaterThan ) {
  CoordPair coord_pair1( 10, 15 );
  CoordPair coord_pair2( 5, 7 );
  CoordPair coord_pair3( 10, 15 );

  ASSERT_TRUE( coord_pair1 > coord_pair2 );
  ASSERT_FALSE( coord_pair1 > coord_pair3 );
  ASSERT_FALSE( coord_pair2 > coord_pair1 );

  ASSERT_EQ( coord_pair1.x_, 10 );
  ASSERT_EQ( coord_pair1.y_, 15 );
  ASSERT_EQ( coord_pair2.x_, 5 );
  ASSERT_EQ( coord_pair2.y_, 7 );
  ASSERT_EQ( coord_pair3.x_, 10 );
  ASSERT_EQ( coord_pair3.y_, 15 );
}

TEST( CoordPairTest, operatorGreaterThanOrEqual ) {
  CoordPair coord_pair1( 10, 15 );
  CoordPair coord_pair2( 5, 7 );
  CoordPair coord_pair3( 10, 15 );

  ASSERT_TRUE( coord_pair1 >= coord_pair2 );
  ASSERT_TRUE( coord_pair1 >= coord_pair3 );
  ASSERT_FALSE( coord_pair2 >= coord_pair1 );

  ASSERT_EQ( coord_pair1.x_, 10 );
  ASSERT_EQ( coord_pair1.y_, 15 );
  ASSERT_EQ( coord_pair2.x_, 5 );
  ASSERT_EQ( coord_pair2.y_, 7 );
  ASSERT_EQ( coord_pair3.x_, 10 );
  ASSERT_EQ( coord_pair3.y_, 15 );
}

TEST( CoordPairTest, distanceFrom ) {
  CoordPair coord_pair1( 10, 15 );
  CoordPair coord_pair2( 7, 11 );

  double distance = coord_pair1.distanceFrom( coord_pair2 );

  ASSERT_EQ( distance, 5 );
}

// NOLINTEND(-Wunused-value)