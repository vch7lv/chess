#include <vector>

enum Color : unsigned char
{
	WH,						
	BL							
};

enum Piece_type : unsigned char
{
	P,
	K,
	Q,							
	B,
	N,
	R,
	X
};

struct Piece
{
	Piece_type  type = X;
	Color       color = WH;

	Piece() = default;
	Piece(Piece_type type) : type(type), color(WH) {}
	Piece(Piece_type type, Color color) : type(type), color(color) {}
};

struct Square
{
	unsigned char x;
	unsigned char y;
};

const std::vector<std::vector<Piece>> STANDART_CHESS_SETUP =
{
	 {Piece(R, WH), Piece(P, WH), Piece(), Piece(), Piece(), Piece(), Piece(P, BL), Piece(R, BL)},
	 {Piece(N, WH), Piece(P, WH), Piece(), Piece(), Piece(), Piece(), Piece(P, BL), Piece(N, BL)},
	 {Piece(B, WH), Piece(P, WH), Piece(), Piece(), Piece(), Piece(), Piece(P, BL), Piece(B, BL)},
	 {Piece(Q, WH), Piece(P, WH), Piece(), Piece(), Piece(), Piece(), Piece(P, BL), Piece(Q, BL)},
	 {Piece(K, WH), Piece(P, WH), Piece(), Piece(), Piece(), Piece(), Piece(P, BL), Piece(K, BL)},
	 {Piece(B, WH), Piece(P, WH), Piece(), Piece(), Piece(), Piece(), Piece(P, BL), Piece(B, BL)},
	 {Piece(N, WH), Piece(P, WH), Piece(), Piece(), Piece(), Piece(), Piece(P, BL), Piece(N, BL)},
	 {Piece(R, WH), Piece(P, WH), Piece(), Piece(), Piece(), Piece(), Piece(P, BL), Piece(R, BL)}
};

struct Board
{
	std::vector<std::vector<Piece>> pieces = STANDART_CHESS_SETUP;
};
