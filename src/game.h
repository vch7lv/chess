#pragma once
#include "position.h"

struct Game
{
	Position position;

	bool make_move(const Move);
	bool make_promotion(Piece_type piece);

};