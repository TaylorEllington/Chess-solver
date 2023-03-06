#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"
#include "board-utils.h"
#include "move-generator.h"


TEST(PositionTests, PositionEquality){

  Position a ("Pa1", PieceColor::BLACK);
  Position b ("Pa1", PieceColor::BLACK);
  Position c ("Pb1", PieceColor::BLACK);
  Position d ("Pa2", PieceColor::BLACK);
  Position e ("Pb2", PieceColor::BLACK);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
  EXPECT_FALSE( a == d);
  EXPECT_FALSE( a == e);

}

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

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));
  using ::testing::HasSubstr;
  EXPECT_THAT(compiledMoves, HasSubstr("Pe3"));
  EXPECT_THAT(compiledMoves, HasSubstr("Pe4"));
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

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));
  using ::testing::HasSubstr;
  EXPECT_THAT(compiledMoves, HasSubstr("Pe4"));
}

TEST(MovementGeneratorTests, PawnCaptureWhite) {
  Position pieceToMove("Pe3", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("Pd4","Pf4");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);

  EXPECT_EQ(moves.size() , 2);

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));
  using ::testing::HasSubstr;
  EXPECT_THAT(compiledMoves, HasSubstr("Pxf4"));
}

TEST(MovementGeneratorTests, PawnStartingRankBlack) {
  Position pieceToMove("Pe7", PieceColor::BLACK);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 2);

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));
  using ::testing::HasSubstr;
  EXPECT_THAT(compiledMoves, HasSubstr("Pe6"));
  EXPECT_THAT(compiledMoves, HasSubstr("Pe5"));
}

TEST(MovementGeneratorTests, PawnBlockedNoMovesBlack) {
  
  Position pieceToMove("Pe7", PieceColor::BLACK);
  BoardState board = board_utils::BuildBoardFromString("","Pe6");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);

  EXPECT_EQ(moves.size(), 0);

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));
}

TEST(MovementGeneratorTests, PawnOtherPositionBlack) {
  Position pieceToMove("Pe6", PieceColor::BLACK);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 1);

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));
  using ::testing::HasSubstr;
  EXPECT_THAT(compiledMoves, HasSubstr("Pe5"));
}

TEST(MovementGeneratorTests, PawnCaptureBlack) {
  Position pieceToMove("Pe7", PieceColor::BLACK);
  BoardState board = board_utils::BuildBoardFromString("Pd6 Pe6 Pf6","");
  std::vector<Position> moves = move_generator::GeneratePawnMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 2);

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));
  using ::testing::HasSubstr;
  EXPECT_THAT(compiledMoves, HasSubstr("Pxd6"));
  EXPECT_THAT(compiledMoves, HasSubstr("Pxf6"));
}

TEST(MovementGeneratorTests, RookCenterEmptyBoard) {
  Position pieceToMove("Re4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GenerateRookMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 14);

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));
  using ::testing::HasSubstr;
  EXPECT_THAT(compiledMoves, HasSubstr("Re3")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Re2")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Re1")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Re5")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Re6")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Re7")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Re8")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Rd4")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Rc4")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Rb4")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Ra4")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Rf4")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Rg4")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Rh4"));

}

TEST(MovementGeneratorTests, RookCapture) {
  Position pieceToMove("Re4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","Ke3");
  std::vector<Position> moves = move_generator::GenerateRookMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 12);

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));
  using ::testing::HasSubstr;
  EXPECT_THAT(compiledMoves, HasSubstr("Rxe3"));
}

TEST(MovementGeneratorTests, KnightCenterEmptyBoard) {
  Position pieceToMove("Ke4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GenerateKnightMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 8);

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));
  using ::testing::HasSubstr; 
  EXPECT_THAT(compiledMoves, HasSubstr("Kg5")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kf6")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kc5")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kd6")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kc3")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kd2")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kg3")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kf2")); 
}

TEST(MovementGeneratorTests, KnightCapture) {

  using ::testing::HasSubstr;

  Position pieceToMove("Ke4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","Pg5");
  std::vector<Position> moves = move_generator::GenerateKnightMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 8);

  std::string compiledMoves = board_utils::joinAllMoves( board_utils::movesToStrings(moves));

  using ::testing::HasSubstr;
  EXPECT_THAT(compiledMoves, HasSubstr("Kxg5")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kf6")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kc5")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kd6")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kc3")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kd2")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kg3")); 
  EXPECT_THAT(compiledMoves, HasSubstr("Kf2")); 
}

TEST(MovementGeneratorTests, BishopCenterEmptyBoard) {
  Position pieceToMove("Be4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GenerateBishiopMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 13);

  std::vector<std::string> strs = board_utils::movesToStrings(moves);
  std::string compiledMoves = board_utils::joinAllMoves(strs);

  using ::testing::HasSubstr;
  EXPECT_THAT(compiledMoves, HasSubstr("Bf5"));
  EXPECT_THAT(compiledMoves, HasSubstr("Bg6"));
  EXPECT_THAT(compiledMoves, HasSubstr("Bh7"));
  EXPECT_THAT(compiledMoves, HasSubstr("Bf3"));
  EXPECT_THAT(compiledMoves, HasSubstr("Bg2"));
  EXPECT_THAT(compiledMoves, HasSubstr("Bh1"));
  EXPECT_THAT(compiledMoves, HasSubstr("Bd3"));
  EXPECT_THAT(compiledMoves, HasSubstr("Bc2"));
  EXPECT_THAT(compiledMoves, HasSubstr("Bb1"));
  EXPECT_THAT(compiledMoves, HasSubstr("Bd5"));
  EXPECT_THAT(compiledMoves, HasSubstr("Bc6"));
  EXPECT_THAT(compiledMoves, HasSubstr("Bb7"));
  EXPECT_THAT(compiledMoves, HasSubstr("Ba8"));
}

TEST(MovementGeneratorTests, BishopCapture) {
  Position pieceToMove("Be4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","Kd5");
  std::vector<Position> moves = move_generator::GenerateBishiopMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 10);

  std::vector<std::string> strs = board_utils::movesToStrings(moves);
  std::string compiledMoves = board_utils::joinAllMoves(strs);

  using ::testing::HasSubstr;
  // only need to test that the capture move is valid
  EXPECT_THAT(compiledMoves, HasSubstr("Bxd5"));
}


TEST(MovementGeneratorTests, QueenCenterEmptyBoard) {
  Position pieceToMove("Qe4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","");
  std::vector<Position> moves = move_generator::GenerateQueenMoves(pieceToMove, board);

  EXPECT_EQ(moves.size(),27);
  //Generate queen moves is a composite of rook and bishop moves, so we dont benefit from testing 
  // the output if the other routines are working
}

TEST(MovementGeneratorTests, QueenCapture) {
  Position pieceToMove("Qe4", PieceColor::WHITE);
  BoardState board = board_utils::BuildBoardFromString("","Ke7");
  std::vector<Position> moves = move_generator::GenerateQueenMoves(pieceToMove, board);
  EXPECT_EQ(moves.size(), 26);

  std::vector<std::string> strs = board_utils::movesToStrings(moves);
  std::string compiledMoves = board_utils::joinAllMoves(strs);
  using::testing::HasSubstr;
  // only need to test that the capture move is valid
  EXPECT_THAT(compiledMoves, HasSubstr("Qxe7"));
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

TEST(MovementGeneratorTests, StartingBoardTests){
  BoardState board = board_utils::BuildBoardFromString("Pa2 Pb2 Pc2 Pd2 Pe2 Pf2 Pg2 Ph2 Ra1 Nb1 Bc1 Qd1 Ke1 Bf1 Ng1 Rh1 ","");

  Position king("Ke1", PieceColor::WHITE);
  std::vector<Position> kingMoves = move_generator::GenerateKingMoves(king, board);
  EXPECT_EQ(kingMoves.size(), 0);

  Position rook("Ra1", PieceColor::WHITE);
  std::vector<Position> rookMoves = move_generator::GenerateRookMoves(rook, board);
  EXPECT_EQ(rookMoves.size(), 0);

  Position Knight("Nb1", PieceColor::WHITE);
  std::vector<Position> KnightMoves = move_generator::GenerateKnightMoves(Knight, board);
  EXPECT_EQ(KnightMoves.size(), 2);

  Position bishop("Bc1", PieceColor::WHITE);
  std::vector<Position> bishopMoves = move_generator::GenerateBishiopMoves(bishop, board);
  EXPECT_EQ(bishopMoves.size(), 0);
}