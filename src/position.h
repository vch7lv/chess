#pragma once
#include <vector>
#include "game_exception.h"


enum Color : unsigned char
{
	WHITE = 1,						
	BLACK = 0,
};

Color operator ! (Color color);

enum Piece_type : unsigned char
{
	PAWN,
	KING,
	QUEEN,							
	BISHOP,
	KNIGHT,
	ROOK,
	EMPTY
};
enum Game_result : unsigned char
{
	DRAW,
	BLACK_WIN,
	WHITE_WIN
};

struct Piece
{
	Piece_type  type  = Piece_type::EMPTY;
	Color       color;
};

struct Point
{
	private:
		signed char x = 8;
		signed char y = 8;

	public:
		Point() = default;
		Point(signed char x, signed char y);

		bool operator == (Point other) const;
		Point operator + (Point other) const;
		Point operator * (signed char scalar) const;

		signed char get_x() const;
		signed char get_y() const;


		bool is_valid();
};

struct Move
{
	Point from;
	Point to;

	Move(Point from, Point to);

	Move& operator = (const Move& other) = default;
	bool operator == (const Move& other) const;

	private:
		Move() : from(Point(0,0)), to(Point(0, 0)) {}
	public:
		static const Move INVALID_MOVE;
};

struct Board
{
	std::vector<std::vector<Piece>> pieces
	{
		{Piece(Piece_type::ROOK, Color::WHITE), Piece(Piece_type::PAWN, Color::WHITE), Piece(), Piece(), Piece(), Piece(), Piece(Piece_type::PAWN, Color::BLACK), Piece(Piece_type::ROOK, Color::BLACK)},
		{ Piece(Piece_type::KNIGHT, Color::WHITE), Piece(Piece_type::PAWN, Color::WHITE), Piece(), Piece(), Piece(), Piece(), Piece(Piece_type::PAWN, Color::BLACK), Piece(Piece_type::KNIGHT, Color::BLACK) },
		{ Piece(Piece_type::BISHOP, Color::WHITE), Piece(Piece_type::PAWN, Color::WHITE), Piece(), Piece(), Piece(), Piece(), Piece(Piece_type::PAWN, Color::BLACK), Piece(Piece_type::BISHOP, Color::BLACK) },
		{ Piece(Piece_type::QUEEN, Color::WHITE), Piece(Piece_type::PAWN, Color::WHITE), Piece(), Piece(), Piece(), Piece(), Piece(Piece_type::PAWN, Color::BLACK), Piece(Piece_type::QUEEN, Color::BLACK) },
		{ Piece(Piece_type::KING, Color::WHITE), Piece(Piece_type::PAWN, Color::WHITE), Piece(), Piece(), Piece(), Piece(), Piece(Piece_type::PAWN, Color::BLACK), Piece(Piece_type::KING, Color::BLACK) },
		{ Piece(Piece_type::BISHOP, Color::WHITE), Piece(Piece_type::PAWN, Color::WHITE), Piece(), Piece(), Piece(), Piece(), Piece(Piece_type::PAWN, Color::BLACK), Piece(Piece_type::BISHOP, Color::BLACK) },
		{ Piece(Piece_type::KNIGHT, Color::WHITE), Piece(Piece_type::PAWN, Color::WHITE), Piece(), Piece(), Piece(), Piece(), Piece(Piece_type::PAWN, Color::BLACK), Piece(Piece_type::KNIGHT, Color::BLACK) },
		{ Piece(Piece_type::ROOK, Color::WHITE), Piece(Piece_type::PAWN, Color::WHITE), Piece(), Piece(), Piece(), Piece(), Piece(Piece_type::PAWN, Color::BLACK), Piece(Piece_type::ROOK, Color::BLACK) }
	};

	Piece& operator [](Point point);
	std::vector<Piece>& operator [](size_t i);
	Piece operator [](Point point) const;
	std::vector<Piece> operator [](size_t i) const;
};


struct Game;

class Position
{
	friend struct Game;


	Board board;

	bool IS_WHITE_CASTLE_POSSIBLE;
	bool IS_WHITE_LONG_CASTLE_POSSIBLE;
	bool IS_BLACK_CASTLE_POSSIBLE;
	bool IS_BLACK_LONG_CASTLE_POSSIBLE;

	bool IS_GAME_OVER = false;
	bool IS_PROMOTION_POSSIBLE = false;

	unsigned short move_counter = 1;

	Color WHOOSE_MOVE = Color::WHITE;

	Point white_king {4,0};
	Point black_king {4,7};
	Point promotion_square;
	Move  last_move = Move(Point(0,0), Point(7,7));


	static bool is_beaten_by(Color color, Point point, const Position&);
	static bool is_checked(Color color, const Position&);
	static bool is_checkmated(Color color, const Position&);
	static bool is_castle_possible(Color color, const Position&);
	static bool is_long_castle_possible(Color color, const Position&);

	std::vector<Move> get_possible_moves(Color color) const;

};
