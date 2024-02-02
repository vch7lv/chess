#include "position.h"
#include "game_exception.h"
#include <vector>


Color operator ! (Color color)
{
	if (color == Color::WHITE)
		return Color::BLACK;
	else
		return Color::WHITE;
}

Point::Point(signed char x, signed char y) : x(x), y(y) {}
bool Point::operator == (Point other) const
{
	return (x == other.x && y == other.y);
}
Point Point::operator + (Point other) const
{
	return Point(this->x + other.x, this->y + other.y);
}
Point Point::operator * (signed char scalar) const
{
	return Point(this->x * scalar, this->y * scalar);
}
signed char Point::get_x() const
{
	return x;
}
signed char Point::get_y() const
{
	return y;
}



Move::Move(Point _from, Point _to)
{
	if (from != to && from.is_valid() && to.is_valid())
	{
		from = _from;
		to = _to;
	}
}
bool Move::operator == (const Move& other) const
{
	return (to == other.to && from == other.from);
}


Piece& Board::operator [](Point point)
{
	signed char x = point.get_x();
	signed char y = point.get_y();

	return Board::pieces[x][y];
}
std::vector<Piece>& Board::operator [](size_t i)
{
	return Board::pieces[i];
}
Piece Board::operator [](Point point) const
{
	signed char x = point.get_x();
	signed char y = point.get_y();

	return Board::pieces[x][y];
}
std::vector<Piece> Board::operator [](size_t i) const
{
	return Board::pieces[i];
}

bool Position::is_beaten_by(Color color, Point point, const Position& position)
{
	std::vector<Point> knight_moves {{1,2},{2,1},{1,-2},{2,-1},{-1,2},{-2,1},{-1,-2},{-2,-1}};
	std::vector<Point> bishop_moves {{1,1},{1,-1},{-1,1},{-1,-1}};
	std::vector<Point> rook_moves   {{1,0},{-1,0},{0,1},{0,-1} };
	std::vector<Point> pawn_moves;

	if (Color::WHITE == color)
		pawn_moves = { {1,1},{1,-1} };
	else
		pawn_moves = {{-1,1},{-1,-1}};

	//check pawn moves;
	for (auto move : pawn_moves)
	{
		if ((point + move).is_valid())
		{
			auto [piece_type, piece_color] = position.board[point + move];
			if (piece_type == PAWN && piece_color == color)
				return true;
		}
	}

	//check knight moves;
	for (auto move : knight_moves)
	{
		if ((point + move).is_valid())
		{
			auto [piece_type, piece_color] = position.board[point + move];
			if (piece_type == KNIGHT && piece_color == color) 
				return true;
		}
	}

	//check rook moves;
	for (auto move : rook_moves)
	for (int len = 1; len <= 8; ++len)
	{
		if ((point + move * len).is_valid())
		{
			auto [piece_type, piece_color] = position.board[point + move * len];

			if (piece_type == EMPTY) continue;
			if (piece_color != color) break;
			if (piece_type == QUEEN || piece_type == ROOK) return true;
		}
		else
		{
			break;
		}
	}

	//check bishop moves
	for (auto move : bishop_moves)
	for (int len = 1; len <= 8; ++len)
	{
		if ((point + move * len).is_valid())
		{
			auto [piece_type, piece_color] = position.board[point + move * len];

			if (piece_type == EMPTY) continue;
			if (piece_color != color) break;
			if (piece_type == QUEEN || piece_type == BISHOP) return true;
		}
		else
		{
			break;
		}
	}

	return false;
}
bool Position::is_checked(Color color, const Position& position)
{
	Point king = (color == WHITE ? position.white_king : position.black_king);
	Color opposite_for_king_color = !color;

	return is_beaten_by(opposite_for_king_color, king);
}
bool Position::is_checkmated(Color color, const Position& position)
{
	return (color == position.WHOOSE_MOVE 
		    && is_checked(color, position)
		    && (position.get_possible_moves(color)).size() == 0);
}
std::vector<Move> Position::get_possible_moves(Color color) const
{
	if (color != WHOOSE_MOVE) return {};

	std::vector<Point> knight_moves{ {1,2},{2,1},{1,-2},{2,-1},{-1,2},{-2,1},{-1,-2},{-2,-1} };
	std::vector<Point> bishop_moves{ {1,1},{1,-1},{-1,1},{-1,-1} };
	std::vector<Point> rook_moves{ {1,0},{-1,0},{0,1},{0,-1} };

	std::vector<Move> Moves;

	for (size_t i = 0; i < 8; ++i)
	for (size_t j = 0; j < 8; ++j)
	{
		Point from(i, j);
		Point to;

		const auto& [piece_type, piece_color] = board[i][j];

		auto tmp_position = *this;
		Piece deleted_piece;

		if (piece_type != EMPTY && piece_color == color)
		{
			if (piece_type == PAWN && piece_color == WHITE)
			{
				to = from + Point(1, 0);
				if (to.is_valid()
					&& board[to].type == EMPTY)
				{
					std::swap(tmp_position.board[from], tmp_position.board[to]);

					if (!is_checked(color, tmp_position))
						Moves.push_back(Move(from, to));

					std::swap(tmp_position.board[from], tmp_position.board[to]);
				}

				if (from.get_x() == 1)
				{
					to = from + Point(2, 0);
					if (to.is_valid()
						&& board[to].type == EMPTY
						&& board[from + Point(1, 0)].type == EMPTY)
					{
						std::swap(tmp_position.board[from], tmp_position.board[to]);

						if (!is_checked(color, tmp_position))
							Moves.push_back(Move(from, to));

						std::swap(tmp_position.board[from], tmp_position.board[to]);
					}
				}
			}
			if (piece_type == PAWN && piece_color == BLACK)
			{
				if ((from + {}).is_valid())
			}
			if (piece_type == KING)
			{

			}
			if (piece_type == KNIGHT)
			{

			}
			if (piece_type == BISHOP || piece_type == QUEEN)
			{

			}
			if (piece_type == ROOK || piece_type == QUEEN)
			{

			}
		}
	}
}
bool Position::is_castle_possible(Color color, const Position& position)
{
	if (color == Color::WHITE)
	{
		if (!position.IS_WHITE_CASTLE_POSSIBLE
		|| (is_beaten_by(Color::BLACK, {4,0}, position))
		|| (is_beaten_by(Color::BLACK, {5,0}, position))
		|| (is_beaten_by(Color::BLACK, {6,0}, position))) return false;
	}
	else
	{
		if (!position.IS_BLACK_CASTLE_POSSIBLE
		|| (is_beaten_by(Color::WHITE, { 4,7 }, position))
		|| (is_beaten_by(Color::WHITE, { 5,7 }, position))
		|| (is_beaten_by(Color::WHITE, { 6,7 }, position))) return false;
	}

	return true;
}
bool Position::is_long_castle_possible(Color color, const Position& position)
{
	if (color == Color::WHITE)
	{
		if (!position.IS_WHITE_LONG_CASTLE_POSSIBLE
			|| (is_beaten_by(Color::BLACK, { 2,0 }, position))
			|| (is_beaten_by(Color::BLACK, { 3,0 }, position))
			|| (is_beaten_by(Color::BLACK, { 4,0 }, position))) return false;
	}
	else
	{
		if (!position.IS_BLACK_LONG_CASTLE_POSSIBLE
			|| (is_beaten_by(Color::WHITE, { 2,7 }, position))
			|| (is_beaten_by(Color::WHITE, { 3,7 }, position))
			|| (is_beaten_by(Color::WHITE, { 4,7 }, position))) return false;
	}

	return true;
}
