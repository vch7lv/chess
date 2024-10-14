#pragma once
#include "ChessBoard.h"



std::uint64_t piece_hash::operator () (const Piece& piece) const
{
    return ((int)piece.type << 32) + (std::uint64_t)((int)piece.color);
}