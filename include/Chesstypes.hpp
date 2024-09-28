#pragma once
#include <string>
#include <iostream>

enum class PieceColor 
{
    EMPTY,
    BLACK,
    WHITE
};

PieceColor getOppositeColor(PieceColor color) {
    if (color == PieceColor::BLACK) return PieceColor::WHITE;
    if (color == PieceColor::WHITE) return PieceColor::BLACK;
    return PieceColor::EMPTY;
}


enum class PieceType
{
    EMPTY,
    KING,
    ROOK,
    BISHOP,
    KNIGHT,
    QUEEN,
    PAWN
};


struct Piece
{
    PieceColor color;
    PieceType type;

    bool is_white() const {
        return color == PieceColor::WHITE;
    }
    bool is_black() const {
        return color == PieceColor::BLACK;
    }
    bool is_empty() const {
        return color == PieceColor::EMPTY;
    }
    bool is_pawn() const {
        return type == PieceType::PAWN;
    }
    bool is_rook() const {
        return type == PieceType::ROOK;
    }
    bool is_bishop() const {
        return type == PieceType::BISHOP;
    }
    bool is_knight() const {
        return type == PieceType::KNIGHT;
    }
    bool is_king() const {
        return type == PieceType::KING;
    }
    bool is_queen() const {
        return type == PieceType::QUEEN;
    }
};


Piece E() { 
    return {PieceColor::EMPTY, PieceType::EMPTY};
}

Piece WK() { 
    return {PieceColor::WHITE, PieceType::KING};
}
Piece WR() { 
    return {PieceColor::WHITE, PieceType::ROOK};
}
Piece WB() { 
    return {PieceColor::WHITE, PieceType::BISHOP};
}
Piece WKN() { 
    return {PieceColor::WHITE, PieceType::KNIGHT};
}
Piece WQ() { 
    return {PieceColor::WHITE, PieceType::QUEEN};
}
Piece WP() { 
    return {PieceColor::WHITE, PieceType::PAWN};
}

Piece BK() { 
    return {PieceColor::BLACK, PieceType::KING};
}
Piece BR() { 
    return {PieceColor::BLACK, PieceType::ROOK};
}
Piece BB() { 
    return {PieceColor::BLACK, PieceType::BISHOP};
}
Piece BKN() {
    return {PieceColor::BLACK, PieceType::KNIGHT};
}
Piece BQ() { 
    return {PieceColor::BLACK, PieceType::QUEEN};
}
Piece BP() { 
    return {PieceColor::BLACK, PieceType::PAWN};
}


struct Point 
{
    int x;
    int y;

    bool is_on_board() {
        return ( x >= 0 && y >= 0 && x < 8 && y < 8);
    }

    Point& operator += (Point rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
};


struct Move
{
    Point from;
    Point to;
};


struct Position
{
    Piece board[8][8] = 
    {
        {WR(),WP(),E(),E(),E(),E(),BP(),BR()},
        {WB(),WP(),E(),E(),E(),E(),BP(),BB()},
        {WKN(),WP(),E(),E(),E(),E(),BP(),BKN()},
        {WK(),WP(),E(),E(),E(),E(),BP(),BK()},
        {WQ(),WP(),E(),E(),E(),E(),BP(),BQ()},
        {WKN(),WP(),E(),E(),E(),E(),BP(),BKN()},
        {WB(),WP(),E(),E(),E(),E(),BP(),BB()},
        {WR(),WP(),E(),E(),E(),E(),BP(),BR()}
    };

    PieceColor turn = PieceColor::WHITE;

    bool IS_WHITE_CASTLE_POSSIBLE = true;
    bool IS_BLACK_CASTLE_POSSIBLE = true;
    bool IS_WHITE_LONG_CASTLE_POSSIBLE = true;
    bool IS_BLACK_LONG_CASTLE_POSSIBLE = true;

    unsigned short moveCounter = 1;

    Move lastMove = {{-1,-1}, {-1,-1}};
};

void print_position(const Position& pos, bool verbose = false) {
    for (int x = 7; x >= 0; --x)
    {
        for (int y = 0; y < 8; ++y)
        {
            auto piece = pos.board[y][x];
            std::string str;

            if (piece.is_white()) str += "W";
            if (piece.is_black()) str += "B";
            if (piece.is_bishop()) str += "B";
            if (piece.is_rook()) str += "R";
            if (piece.is_knight()) str += "KN";
            if (piece.is_king()) str += "K";
            if (piece.is_queen()) str += "Q";
            if (piece.is_pawn()) str += "P";

            if (str.empty()) str += " .";

            str += std::string(3-(int)str.size(), ' ');

            std::cout << str << ' ';
        }
        std::cout << '\n';
    }

    if (verbose) {
        std::cout << '\n';

        std::cout << "turn: ";
        std::cout << (pos.turn == PieceColor::WHITE ? "white" : "black") << '\n';

        std::cout << "is white castle possible: ";
        std::cout << (pos.IS_WHITE_CASTLE_POSSIBLE ? "true" : "false") << '\n';

        std::cout << "is black castle possible: "; 
        std::cout << (pos.IS_BLACK_CASTLE_POSSIBLE ? "true" : "false") << '\n';

        std::cout << "is white long castle possible:: "; 
        std::cout << (pos.IS_WHITE_LONG_CASTLE_POSSIBLE ? "true" : "false") << '\n';

        std::cout << "is black long castle possible: "; 
        std::cout << (pos.IS_BLACK_LONG_CASTLE_POSSIBLE ? "true" : "false") << '\n';

        std::cout << "move counter: " << pos.moveCounter << '\n';

        std::cout << "last move: ";
        std::cout << '{' << pos.lastMove.from.x << ',' << pos.lastMove.from.y << '}';
        std::cout << " -> ";
        std::cout << '{' << pos.lastMove.to.x << ',' << pos.lastMove.to.y << "}\n";
    }

}

