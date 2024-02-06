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
Point operator * (Point point, signed char scalar)
{
	return Point(point.get_x() * scalar, point.get_y() * scalar);
}
signed char Point::get_x() const
{
	return x;
}
signed char Point::get_y() const
{
	return y;
}
bool Point::is_valid() const
{
	if (this->x >= 0 && this->x < 8 && this->y >= 0 && this->y < 8) 
		return true;
	return false;
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



const Move Position::WHITE_CASTLE         = Move(Point(4, 0), Point(6, 0));
const Move Position::WHITE_LONG_CASTLE    = Move(Point(4, 0), Point(2, 0));
const Move Position::BLACK_CASTLE         = Move(Point(4, 7), Point(6, 7));
const Move Position::BLACK_LONG_CASTLE    = Move(Point(4, 7), Point(2, 7));

const std::vector<Point> Position::knight_moves     = { {1,2},{2,1},{1,-2},{2,-1},{-1,2},{-2,1},{-1,-2},{-2,-1} };
const std::vector<Point> Position::bishop_moves     = { {1,1},{1,-1},{-1,1},{-1,-1} };
const std::vector<Point> Position::rook_moves       = { {1,0},{-1,0},{0,1},{0,-1} };
const std::vector<Point> Position::king_moves       = { {1,1},{1,-1},{-1,1},{-1,-1}, {1,0},{-1,0},{0,1},{0,-1} };
const std::vector<Point> Position::black_pawn_eat_moves = { {1,-1},{-1,-1} };
const std::vector<Point> Position::white_pawn_eat_moves = { {1, 1},{-1, 1} };


bool Position::is_beaten_by(Color color, Point point, const Position& position)
{
	//check pawn moves;
	auto pawn_moves = (color == WHITE ? white_pawn_eat_moves : black_pawn_eat_moves);
	for (auto move : pawn_moves)
	{
		Point to = point + (move * -1);

		if (!to.is_valid()) continue;

		auto [piece_type, piece_color] = position.board[to];
		if (piece_type == PAWN && piece_color == color)
			return true;
	}

	//check knight moves;
	for (auto move : knight_moves)
	{
		Point to = point + move;
		if (!to.is_valid()) continue;

		auto [piece_type, piece_color] = position.board[to];
		if (piece_type == KNIGHT && piece_color == color) 
			return true;
	}

	//check rook && queen moves;
	for (auto move : rook_moves)
	for (signed char len = 1; len <= 7; ++len)
	{
		Point to = point + move * len;
		if (!to.is_valid()) break;

		auto [piece_type, piece_color] = position.board[to];

		if (piece_type == EMPTY) continue;

		if (piece_type == QUEEN || piece_type == ROOK) return true;
		else break;

	}

	//check bishop && queen moves;
	for (auto move : bishop_moves)
	for (signed char len = 1; len <= 7; ++len)
	{
		Point to = point + move * len;

		if (!to.is_valid()) break;

		auto [piece_type, piece_color] = position.board[to];

		if (piece_type == EMPTY) continue;
		if (piece_type == QUEEN || piece_type == BISHOP) return true;
		else break;
	}

	//check king moves;
	for (auto move : king_moves)
	{
		Point to = point + move;

		if (!to.is_valid()) break;

		auto [piece_type, piece_color] = position.board[to];
		if (piece_type == KING) return true;
	}

	return false;
}

bool Position::is_checked(Color color, const Position& position)
{
	Point king = (color == WHITE ? position.white_king : position.black_king);
	Color opposite_for_king_color = !color;

	return is_beaten_by(opposite_for_king_color, king, position);
}
bool Position::is_checkmated(Color color, const Position& position)
{
	return (color == position.whoose_move 
		    && is_checked(color, position)
		    && (position.get_possible_moves(color, position)).size() == 0);
}

bool Position::is_castle_possible(Color color, const Position& position)
{
	if (color == Color::WHITE)
	{
		if (!position.is_white_castle_possible
		|| (is_beaten_by(Color::BLACK, {4,0}, position))
		|| (is_beaten_by(Color::BLACK, {5,0}, position))
		|| (is_beaten_by(Color::BLACK, {6,0}, position))
		|| position.board[5][0].type != EMPTY
		|| position.board[6][0].type != EMPTY) return false;
	}
	else
	{
		if (!position.is_black_castle_possible
		|| (is_beaten_by(Color::WHITE, { 4,7 }, position))
		|| (is_beaten_by(Color::WHITE, { 5,7 }, position))
		|| (is_beaten_by(Color::WHITE, { 6,7 }, position))
		|| position.board[5][7].type != EMPTY
		|| position.board[6][7].type != EMPTY) return false;
	}

	return true;
}
bool Position::is_long_castle_possible(Color color, const Position& position)
{
	if (color == Color::WHITE)
	{
		if (!position.is_white_long_castle_possible
			|| (is_beaten_by(Color::BLACK, { 2,0 }, position))
			|| (is_beaten_by(Color::BLACK, { 3,0 }, position))
			|| (is_beaten_by(Color::BLACK, { 4,0 }, position))
			|| position.board[1][0].type != EMPTY
			|| position.board[2][0].type != EMPTY
			|| position.board[3][0].type != EMPTY) return false;
	}
	else
	{
		if (!position.is_black_long_castle_possible
			|| (is_beaten_by(Color::WHITE, { 2,7 }, position))
			|| (is_beaten_by(Color::WHITE, { 3,7 }, position))
			|| (is_beaten_by(Color::WHITE, { 4,7 }, position))
			|| position.board[1][7].type != EMPTY
			|| position.board[2][7].type != EMPTY
			|| position.board[3][7].type != EMPTY) return false;
	}

	return true;
}

std::vector<Move> Position::get_possible_pawn_moves(Color color, Point from, const Position& position)
{
	std::vector<Move> moves;
	Position new_position = position;

	auto pawn_eat_moves = (color == WHITE ? white_pawn_eat_moves : black_pawn_eat_moves);
	signed passant_from_y = (color == WHITE ? 4 : 3);


	for (auto move : pawn_eat_moves)
	{
		Point to = from + move;

		// correct last move for passant
		Point last_move_from 
			= (color == WHITE ? Point(to.get_x(),to.get_y()+1) : Point(to.get_x(),to.get_y()-1));
		Point last_move_to 
			= (color == WHITE ? Point(to.get_x(),to.get_y()-1) : Point(to.get_x(),to.get_y()+1));
		Move correct_last_move = Move(last_move_from, last_move_to);

		auto [piece_type, piece_color] = position.board[to];

		if (!to.is_valid() || (piece_type != EMPTY && piece_color == color))
			continue;

		if (piece_type != EMPTY)
		{
			new_position.board[to] = position.board[from];
			new_position.board[from] = Piece();

			if (!is_checked(color, new_position))
				moves.push_back(Move(from, to));

			new_position.board[to] = position.board[to];
			new_position.board[from] = position.board[from];
		} 
		
		//check passant
		else if (from.get_y() == passant_from_y
			&& position.last_move == correct_last_move
			&& position.board[last_move_to].type == PAWN)
		{
			new_position.board[to] = position.board[from];
			new_position.board[from] = Piece();
			new_position.board[last_move_to] = Piece();

			if (!is_checked(color, new_position))
				moves.push_back(Move(from, to));

			new_position.board[from] = position.board[from];
			new_position.board[to] = position.board[to];
			new_position.board[last_move_to] = position.board[last_move_to];
		}
	}
	
	//add simple pawn move
	
	Point  direction = (color == WHITE ? Point(0, 1) : Point(0, -1));
	signed line_from = (color == WHITE ? 1 : 6);

	for (signed len = 1; len <= 2; ++len)
	{
		auto to = from + (direction * len);
		auto [piece_type, piece_color] = position.board[to];

		if (len == 2 && from.get_y() != line_from) break;
		if (position.board[to].type != EMPTY) break;

		new_position.board[to] = position.board[from];
		new_position.board[from] = Piece();

		if (!is_checked(color, new_position))
			moves.push_back(Move(from, to));

		new_position.board[to] = position.board[to];
		new_position.board[from] = position.board[from];
	}

	return moves;
}

std::vector<Move> Position::get_possible_knight_moves(Color color, Point from, const Position& position) 
{
	std::vector<Move> moves;
	Position new_position = position;

	for (auto move : knight_moves)
	{
		Point to = from + move;

		if (!to.is_valid() || (position.board[to].type != EMPTY && position.board[to].color == color))
			continue;

		new_position.board[to] = position.board[from];
		new_position.board[from] = Piece();

		if (!is_checked(color, new_position))
			moves.push_back(Move(from, to));

		new_position.board[to] = position.board[to];
		new_position.board[from] = position.board[from];
	}

	return moves;
}
std::vector<Move> Position::get_possible_rook_moves(Color color, Point from, const Position& position) 
{
	std::vector<Move> moves;
	Position new_position = position;

	for (auto move : rook_moves)
	for (signed char len = 1; len <= 7; ++len)
	{
		Point to = from + (move * len);

		if (!to.is_valid() || (position.board[to].type != EMPTY && position.board[to].color == color))
			break;

		new_position.board[to] = position.board[from];
		new_position.board[from] = Piece();

		if (!is_checked(color, new_position))
			moves.push_back(Move(from, to));

		new_position.board[to] = position.board[to];
		new_position.board[from] = position.board[from];
	}

	return moves;
}
std::vector<Move> Position::get_possible_bishop_moves(Color color, Point from, const Position& position) 
{
	std::vector<Move> moves;
	Position new_position = position;

	for (auto move : bishop_moves)
	for (signed char  len = 1; len <= 7; ++len)
	{
		Point to = from + (move * len);

		if (!to.is_valid() || (position.board[to].type != EMPTY && position.board[to].color == color))
			break;

		new_position.board[to] = position.board[from];
		new_position.board[from] = Piece();

		if (!is_checked(color, new_position))
			moves.push_back(Move(from, to));

		new_position.board[to] = position.board[to];
		new_position.board[from] = position.board[from];
	}

	return moves;
}
std::vector<Move> Position::get_possible_king_moves(Color color, Point from, const Position& position) 
{
	std::vector<Move> moves;
	Position new_position = position;

	for (auto move : king_moves)
	{
		Point to = from + move;

		if (!to.is_valid() || (position.board[to].type != EMPTY && position.board[to].color == color))
			continue;

		new_position.board[to]   = position.board[from];
		new_position.board[from] = Piece();

		if (!is_checked(color, new_position)) 
			moves.push_back(Move(from, to));

		new_position.board[to]   = position.board[to];
		new_position.board[from] = position.board[from];
	}

	if (is_castle_possible(color, position)) 
		moves.push_back(color == WHITE ? WHITE_CASTLE : BLACK_CASTLE);

	if (is_long_castle_possible(color, position)) 
		moves.push_back(color == WHITE ? WHITE_LONG_CASTLE : BLACK_LONG_CASTLE);

	return moves;
}
std::vector<Move> Position::get_possible_queen_moves(Color color, Point from, const Position& position)
{
	std::vector<Move> moves = get_possible_rook_moves(color, from, position);
	for (auto move : get_possible_bishop_moves(color, from, position))
		moves.push_back(move);
	return moves;
}
std::vector<Move> Position::get_possible_moves(Color color, const Position& position)
{
	std::vector<Move> moves;

	for (signed char i = 0; i < 8; ++i)
	for (signed char j = 0; j < 8; ++j)
	{
		auto [piece_type, piece_color] = position.board[i][j];

		if (piece_type == EMPTY || color != piece_color) continue;
		switch (piece_type)
		{
			case PAWN :
				for (auto move : get_possible_pawn_moves(color, { i,j }, position))
					moves.push_back(move);
				break;
			case KNIGHT:
				for (auto move : get_possible_knight_moves(color, { i,j }, position))
					moves.push_back(move);
				break;
			case BISHOP:
				for (auto move : get_possible_bishop_moves(color, { i,j }, position))
					moves.push_back(move);
				break;
			case ROOK:
				for (auto move : get_possible_rook_moves(color, { i,j }, position))
					moves.push_back(move);
				break;
			case KING:
				for (auto move : get_possible_king_moves(color, { i,j }, position))
					moves.push_back(move);
				break;
			case QUEEN:
				for (auto move : get_possible_queen_moves(color, { i,j }, position))
					moves.push_back(move);
				break;
		}
	}

	return moves;
}
