#include "gtest/gtest.h"
#include "board-utils/board-utils.h"



TEST(BoardUtilitiesTests, ValidBoardPosition) {
  using namespace board_utils;

  Position shouldBeLegal;
  shouldBeLegal.file = 4;
  shouldBeLegal.rank = 4;
  EXPECT_TRUE(isValidPosition(shouldBeLegal));

}

TEST(BoardUtilitiesTests, InvalidBoardPosition) {
  using namespace board_utils;

  Position shouldBeLegal;
  shouldBeLegal.file = 9;
  shouldBeLegal.rank = 4;
  EXPECT_FALSE(isValidPosition(shouldBeLegal));

}

TEST(BoardUtilitiesTests, PositionConstructorFromString) {
  using namespace board_utils;
  Position posFromGoodString1("Kh2", PieceColor::BLACK);

  EXPECT_EQ(posFromGoodString1.rank, 2);
  EXPECT_EQ(posFromGoodString1.file, 8);
  EXPECT_EQ(posFromGoodString1.piece, Piece::KING);
  EXPECT_EQ(posFromGoodString1.color, PieceColor::BLACK);

  Position posFromGoodString2("Na8", PieceColor::BLACK);

  EXPECT_EQ(posFromGoodString2.rank, 8);
  EXPECT_EQ(posFromGoodString2.file, 1);
  EXPECT_EQ(posFromGoodString2.piece, Piece::KNIGHT);
  EXPECT_EQ(posFromGoodString2.color, PieceColor::BLACK);
}


TEST(BoardUtilitiesTests, PositionConstructorFromBadStrings) {
  using namespace board_utils;
  Position posFromString(" K h 2 ", PieceColor::BLACK);

  EXPECT_EQ(posFromString.rank, 2);
  EXPECT_EQ(posFromString.file, 8);
  EXPECT_EQ(posFromString.piece, Piece::KING);
  EXPECT_EQ(posFromString.color, PieceColor::BLACK);
}

TEST(BoardUtilitiesTests, BuildBoardStateFromString){
  std::string WhitePositionsString = "Ke4 Ba2 Bc3";
  std::string BlackPositionsString = "Kf8 Pa3 Pd3";

  BoardState state = board_utils::BuildBoardFromString(WhitePositionsString, BlackPositionsString);

  EXPECT_EQ(state.size(), 6);

}
