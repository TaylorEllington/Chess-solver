#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"
#include "board-utils.h"
#include "move-generator.h"




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




TEST(MovementGeneratorTests, PawnStartingRankWhite) {
  
  Position pieceToMove("Pe2", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);

  EXPECT_EQ(moves.size(), 2);
}

TEST(MovementGeneratorTests, PawnBlockedNoMovesWhite) {
  
  Position pieceToMove("Pe2", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","Pe3");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);

  EXPECT_EQ(moves.size(), 0);
}

TEST(MovementGeneratorTests, PawnOtherPositionWhite) {
  Position pieceToMove("Pe3", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 1);
}

TEST(MovementGeneratorTests, PawnCaptureWhite) {
  Position pieceToMove("Pe3", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("Pd4","Pf4");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);

  EXPECT_EQ(moves.size() , 2);
}

TEST(MovementGeneratorTests, PawnStartingRankBlack) {
  Position pieceToMove("Pe7", PieceColor::BLACK);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 2);
}

TEST(MovementGeneratorTests, PawnBlockedNoMovesBlack) {
  
  Position pieceToMove("Pe7", PieceColor::BLACK);
  BoardState board = board_utils::BuildBoardFromString("","Pe6");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);

  EXPECT_EQ(moves.size(), 0);
}

TEST(MovementGeneratorTests, PawnOtherPositionBlack) {
  Position pieceToMove("Pe6", PieceColor::BLACK);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 1);
}

TEST(MovementGeneratorTests, PawnCaptureBlack) {
  Position pieceToMove("Pe7", PieceColor::BLACK);
  BoardState board = board_utils::BuildBoardFromString("Pd6 Pe6 Pf6","");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 2);
}

TEST(MovementGeneratorTests, RookCenterEmptyBoard) {
  Position pieceToMove("Re4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GenerateRookMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 14);
}

TEST(MovementGeneratorTests, RookCapture) {
  Position pieceToMove("Re4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","Ke3");
  std::vector<Position> moves = move_generator::GenerateRookMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 12);
}

TEST(MovementGeneratorTests, KnightCenterEmptyBoard) {
  Position pieceToMove("Ke4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GenerateKnightMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 8);
}

TEST(MovementGeneratorTests, KnightCapture) {

  using ::testing::HasSubstr;

  Position pieceToMove("Ke4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","Pg5");
  std::vector<Position> moves = move_generator::GenerateKnightMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 8);

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));

  EXPECT_THAT(compiledMoves, HasSubstr("Kxg5"));
}

TEST(MovementGeneratorTests, BishopCenterEmptyBoard) {
  Position pieceToMove("Be4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GenerateBishiopMoves(pieceToMove, board);
  std::vector<std::string> strs = board_utils::movesToStrings(moves);
  EXPECT_EQ(moves.size(), 13);
}

TEST(MovementGeneratorTests, BishopCapture) {
  Position pieceToMove("Be4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","Kd5");
  std::vector<Position> moves = move_generator::GenerateBishiopMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 10);
}


TEST(MovementGeneratorTests, QueenCenterEmptyBoard) {
  Position pieceToMove("Qe4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GenerateQueenMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(),27);
}

TEST(MovementGeneratorTests, QueenCapture) {
  Position pieceToMove("Qe4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","Ke7");
  std::vector<Position> moves = move_generator::GenerateQueenMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 26);
}

TEST(MovementGeneratorTests, KingCenterEmptyBoard) {
  Position pieceToMove("Ke4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GenerateKingMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 8);
}

TEST(MovementGeneratorTests, KingCapture) {

  using ::testing::HasSubstr;

  Position pieceToMove("Ke4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","Re5 Pf3");
  std::vector<Position> moves = move_generator::GenerateKingMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 8);

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));

  EXPECT_THAT(compiledMoves, HasSubstr("Kxe5"));
  EXPECT_THAT(compiledMoves, HasSubstr("Kxf3"));
}

TEST(MovementGeneratorTests, KingCheckRules) {
  Position pieceToMove("", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GenerateKingMoves(pieceToMove, board);
  EXPECT_EQ(1, 1);
}

