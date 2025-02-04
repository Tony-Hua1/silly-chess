#include "utf8_codepoint.h"
#include "chess_pieces.h"


bool ChessPiece::is_opposite_team(const ChessPiece& other) const {
  return (team == WHITE && other.team == BLACK) || (team == BLACK && other.team == WHITE);
}

bool ChessPiece::operator==(const ChessPiece& other) const {
  return utf8_codepoint == other.utf8_codepoint;
}
bool ChessPiece::operator!=(const ChessPiece& other) const {
  return utf8_codepoint != other.utf8_codepoint;
}

ostream& operator<<(ostream& os, const ChessPiece& p) {
  return os << p.utf8_codepoint;
}

void SimpleChessPiece::make_move(Board& board, Move move) const {
  board.make_classical_chess_move(move);
}

void King::get_moves(const Board& board, Cell from, vector<Move>& moves) const {
  for (int x = from.x - 1; x < from.x + 2; ++x) {
    for (int y = from.y - 1; y < from.y + 2; ++y) {
      Cell to(x, y);
      if (from != to && board.contains(to)
          && (board[to] == EMPTY_SPACE || is_opposite_team(board[to]))) {
        moves.emplace_back(from, to);
      }
    }
  }
}

void Queen::get_moves(const Board& board, Cell from, vector<Move>& moves) const {
  // The 8 directions a queen can go...
  Cell directions[] = {
    {-1,  1}, {0,  1}, {1,  1},
    {-1,  0},          {1,  0},
    {-1, -1}, {0, -1}, {1, -1},
  };
  for (Cell direction : directions) {
    for (int steps = 1; ; ++steps) {
      Cell to(from.x + steps * direction.x, from.y + steps * direction.y);
      if (!board.contains(to)) {
        break;
      }
      const ChessPiece& piece = board[to];
      if (piece == EMPTY_SPACE) {
        moves.emplace_back(from, to);
      } else if (is_opposite_team(piece)) {
        moves.emplace_back(from, to);
        break;
      } else {  // if (team == piece.team)
        break;
      }
    }
  }
}

void Bishop::get_moves(const Board& board, Cell from, vector<Move>& moves) const {
  // The 4 directions a bishop can go...
  Cell directions[] = {
    {-1,  1}, {1,  1},
    {-1, -1}, {1, -1},
  };
  for (Cell direction : directions) {
    for (int steps = 1; ; ++steps) {
      Cell to(from.x + steps * direction.x, from.y + steps * direction.y);
      if (!board.contains(to)) {
        break;
      }
      const ChessPiece& piece = board[to];
      if (piece == EMPTY_SPACE) {
        moves.emplace_back(from, to);
      } else if (is_opposite_team(piece)) {
        moves.emplace_back(from, to);
        break;
      } else {  // if (team == piece.team)
        break;
      }
    }
  }
}

void Knight::get_moves(const Board& board, Cell from, vector<Move>& moves) const {
  Cell jumps[] = {
         {-1,  2}, {1,  2},
    {-2,  1},          {2,  1},
    {-2, -1},          {2, -1},
         {-1, -2}, {1, -2},
  };
  for (Cell jump : jumps) {
    Cell to(from.x + jump.x, from.y + jump.y);
    if (board.contains(to)) {
      const ChessPiece& piece = board[to];
      if (piece == EMPTY_SPACE || is_opposite_team(piece)) {
        moves.emplace_back(from, to);
      }
    }
  }
}

void Rook::get_moves(const Board& board, Cell from, vector<Move>& moves) const {
  // The 4 directions a rook can go...
  Cell directions[] = {
              {0,  1},
    {-1,  0},          {1,  0},
              {0, -1},
  };
  for (Cell direction : directions) {
    for (int steps = 1; ; ++steps) {
      Cell to(from.x + steps * direction.x, from.y + steps * direction.y);
      if (!board.contains(to)) {
        break;
      }
      const ChessPiece& piece = board[to];
      if (piece == EMPTY_SPACE) {
        moves.emplace_back(from, to);
      } else if (is_opposite_team(piece)) {
        moves.emplace_back(from, to);
        break;
      } else {  // if (team == piece.team)
        break;
      }
    }
  }
}

void Pawn::get_moves(const Board& board, Cell from, vector<Move>& moves) const {
  Cell to = Cell(from.x, from.y + y_move_steps);
  if (board.contains(to) && board[to] == EMPTY_SPACE) {
    moves.emplace_back(from, to);
  }

  to = Cell(from.x - 1, from.y + y_move_steps);
  if (board.contains(to) && is_opposite_team(board[to])) {
    moves.emplace_back(from, to);
  }

  to = Cell(from.x + 1, from.y + y_move_steps);
  if (board.contains(to) && is_opposite_team(board[to])) {
    moves.emplace_back(from, to);
  }
}

void CheckerPiece::get_moves(const Board& board, Cell from, vector<Move>& moves) const {
  Cell to;

  to = Cell(from.x - 1, from.y + y_move_steps);
  if (board.contains(to) && board[to] == EMPTY_SPACE) {
    moves.emplace_back(from, to);
  }
  if (board.contains(to) && is_opposite_team(board[to])) {
    moves.emplace_back(from, to);
  }

  to = Cell(from.x + 1, from.y + y_move_steps);
  if (board.contains(to) && board[to] == EMPTY_SPACE) {
    moves.emplace_back(from, to);
  }
  if (board.contains(to) && is_opposite_team(board[to])) {
    moves.emplace_back(from, to);
  }
}

const EmptySpace EMPTY_SPACE;
const King WHITE_KING(U'♔', WHITE);
const King BLACK_KING(U'♚', BLACK);
const Queen WHITE_QUEEN(U'♕', WHITE);
const Queen BLACK_QUEEN(U'♛', BLACK);
const Bishop WHITE_BISHOP(U'♗', WHITE);
const Bishop BLACK_BISHOP(U'♝', BLACK);
const Knight WHITE_KNIGHT(U'♘', WHITE);
const Knight BLACK_KNIGHT(U'♞', BLACK);
const Rook WHITE_ROOK(U'♖', WHITE);
const Rook BLACK_ROOK(U'♜', BLACK);
const Pawn WHITE_PAWN(U'♙', WHITE, 1);
const Pawn BLACK_PAWN(U'♟', BLACK, -1);
const CheckerPiece WHITE_CHECKER_PIECE(U'⛀', WHITE, 1);
const CheckerPiece BLACK_CHECKER_PIECE(U'⛂', BLACK, -1);
const map<UTF8CodePoint, const ChessPiece*> ALL_CHESS_PIECES = {
  {EMPTY_SPACE.utf8_codepoint, &EMPTY_SPACE},
  {WHITE_KING.utf8_codepoint, &WHITE_KING},
  {BLACK_KING.utf8_codepoint, &BLACK_KING},
  {WHITE_QUEEN.utf8_codepoint, &WHITE_QUEEN},
  {BLACK_QUEEN.utf8_codepoint, &BLACK_QUEEN},
  {WHITE_BISHOP.utf8_codepoint, &WHITE_BISHOP},
  {BLACK_BISHOP.utf8_codepoint, &BLACK_BISHOP},
  {WHITE_KNIGHT.utf8_codepoint, &WHITE_KNIGHT},
  {BLACK_KNIGHT.utf8_codepoint, &BLACK_KNIGHT},
  {WHITE_ROOK.utf8_codepoint, &WHITE_ROOK},
  {BLACK_ROOK.utf8_codepoint, &BLACK_ROOK},
  {WHITE_PAWN.utf8_codepoint, &WHITE_PAWN},
  {BLACK_PAWN.utf8_codepoint, &BLACK_PAWN},
  {WHITE_CHECKER_PIECE.utf8_codepoint, &WHITE_CHECKER_PIECE},
  {BLACK_CHECKER_PIECE.utf8_codepoint, &BLACK_CHECKER_PIECE},
};
