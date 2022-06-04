#ifndef _UNIT_TEST_CHESS_H_
#define _UNIT_TEST_CHESS_H_

#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::logic_error;
using std::stringstream;

class UnitTestException : public logic_error {
public:
  UnitTestException(const string& err) : logic_error(err) {}
};

template <typename T, typename U>
void assert_equals(const T& expected, const U& actual, const string& error_msg) {
  if (expected != actual) {
    stringstream msg;
    msg << "Expected " << expected << " but got " << actual << ". " << error_msg;
    throw UnitTestException(msg.str());
  }
}

int sum(int a, int b) {
	return a + b;
}

void unit_test_player_name() {
  Board board;
  RandomPlayer white_player(WHITE);
  RandomPlayer black_player(BLACK);
  string name;

  name = white_player.name();
  assert_equals("White", name, "white player.name() in unit_test_name");

  name = black_player.name();
  assert_equals("Black", name, "black_player.name() in unit_test_name");
}

void unit_test_board_get_moves() {
  Board board;
  RandomPlayer white_player(WHITE);
  RandomPlayer black_player(BLACK);
  vector<Move> moves = board.get_moves();
  assert_equals(false, moves.empty(), "Board::get_moves() in unit_test_board_get_moves");
}

void unit_test_board_make_move() {
  Board original_board;
  Board new_board;

  Cell from(1, 0); // b1 or (1, 0)
  Cell to(0, 2); // a3 or (0, 2)
  Move move(from, to);
  new_board.make_move(move);
  
  vector<Move> original_moves = original_board.get_moves();
  vector<Move> new_moves = new_board.get_moves();

  assert_equals(false, original_moves[0] == new_moves[0], "Board::make_move(b1, a3) in unit_test_board_make_moves");
}

void unit_test_reset_board() {
  Board original_board;
  Board new_board;

  Cell from(1, 0); // b1 or (1, 0)
  Cell to(0, 2); // a3 or (0, 2)
  Move move(from, to);
  new_board.make_move(move);
  new_board.reset_board();

  vector<Move> original_moves = original_board.get_moves();
  vector<Move> new_moves = new_board.get_moves();

  for (int i = 0; i < original_moves.size(); ++i) {
    assert_equals(true, original_moves[i] == new_moves[i], "Board::board_reset() after making a move in unit_test_reset_board");
  }
}

void unit_test_chesspiece_is_opposite_team() {
  Board board;

  Cell from(1, 0); // b1 or (1, 0)
  Cell to(0, 2); // a3 or (0, 2)
  Move move(from, to);

  assert_equals(false, board[move.from].is_opposite_team(board[move.to]), "ChessPiece::is_opposite_team is false in unit_test_chesspiece_is_opposite_team");

  board.make_move(move);
  Cell from2(0, 2);
  Cell to2(1, 4);
  Move move2(from2, to2);
  board.make_move(move2);
  Cell from3(1, 4);
  Cell to3(0, 6);
  Move move3(from3, to3);
  board.make_move(move3);
  Cell from4(0, 6);
  Cell to4(2, 5);
  Move move4(from4, to4);
  board.make_move(move4);
  Cell from5(2, 5);
  Cell to5(3, 7);
  Move move5(from5, to5);

  assert_equals(true, board[move5.from].is_opposite_team(board[move5.to]), "ChessPiece::is_opposite_team is true in unit_test_chesspiece_is_opposite_team");
}

void unit_test_board_contains() {
  Board board;
  
  Cell first_cell(0, 0);
  assert_equals(true, board.contains(first_cell), "board.contains(cell(0, 0) in unit_test_board_contains");

  Cell fake_cell(10, 10);
  assert_equals(false, board.contains(fake_cell), "board.contains(cell(10, 10) in unit_test_board_contains");
}

#endif // UNIT_TEST_CHESS_H