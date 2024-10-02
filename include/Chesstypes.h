#pragma once
#include <string>
#include <iostream>
#include <vector>

enum class PieceColor 
{
    EMPTY,
    BLACK,
    WHITE
};

PieceColor getOppositeColor(PieceColor color);


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

    bool is_white() const;
    bool is_black() const;
    bool is_empty() const;
    bool is_pawn() const ;
    bool is_rook() const;
    bool is_bishop() const;
    bool is_knight() const;
    bool is_king() const;
    bool is_queen() const;
};


Piece E();
Piece WK();
Piece WR();
Piece WB();
Piece WKN();
Piece WQ();
Piece WP();
Piece BK();
Piece BR();
Piece BB();
Piece BKN();
Piece BQ();
Piece BP();


struct Point 
{
    int x;
    int y;

    bool is_on_board() const;

    Point& operator += (Point rhs);
    Point& operator *= (int num);
    bool operator == (const Point& rhs) const;
};

Point operator + (Point lhs, Point rhs);
Point operator * (Point lhs, int num);


struct Move
{
    Point from;
    Point to;

    bool is_on_board() const;
    bool operator == (const Move& rhs) const;
};

Move get_castle_move(PieceColor playerColor);
Move get_long_castle_move(PieceColor playerColor);
Point get_pawn_move(PieceColor playerColor);
std::vector<Point> get_attack_pawn_moves(PieceColor playerColor);


struct ChessPosition
{
    Piece board[8][8] = 
    {
        {WR(),WP(),E(),E(),E(),E(),BP(),BR()},
        {WKN(),WP(),E(),E(),E(),E(),BP(),BKN()},
        {WB(),WP(),E(),E(),E(),E(),BP(),BB()},
        {WQ(),WP(),E(),E(),E(),E(),BP(),BQ()},
        {WK(),WP(),E(),E(),E(),E(),BP(),BK()},
        {WB(),WP(),E(),E(),E(),E(),BP(),BB()},
        {WKN(),WP(),E(),E(),E(),E(),BP(),BKN()},
        {WR(),WP(),E(),E(),E(),E(),BP(),BR()}
    };

    PieceColor turn = PieceColor::WHITE;

    bool IS_WHITE_CASTLE_POSSIBLE = true;
    bool IS_BLACK_CASTLE_POSSIBLE = true;
    bool IS_WHITE_LONG_CASTLE_POSSIBLE = true;
    bool IS_BLACK_LONG_CASTLE_POSSIBLE = true;

    unsigned short moveCounter = 1;

    Move lastMove = {{-1,-1}, {-1,-1}};

    Point whiteKingPos {4,0};
    Point blackKingPos {4,7};

    bool NEED_PROMOTION = false;
    Point promotion_square;

    public:

        bool make_move(PieceColor playerColor, Move move);
        bool make_promotion(PieceColor playerColor, PieceType newPiece);

        bool is_checked(PieceColor playerColor);
        bool is_checkmated(PieceColor playerColor);


    private:
        std::vector<Move> get_valid_pawn_moves(Point from, PieceColor player);
        std::vector<Move> get_valid_rook_moves(Point from, PieceColor player);
        std::vector<Move> get_valid_knight_moves(Point from, PieceColor player);
        std::vector<Move> get_valid_bishop_moves(Point from, PieceColor player);
        std::vector<Move> get_valid_queen_moves(Point from, PieceColor player);
        std::vector<Move> get_valid_king_moves(Point from, PieceColor player);

        std::vector<Move> get_valid_moves(PieceType type, Point from, PieceColor player);



        bool is_valid_move(Move move, PieceColor playerColor);

        bool is_passant_square(Point square, PieceColor playerColor);
        bool is_prohibited_move(Move move, PieceColor player);

        bool is_castle_possible(PieceColor playerColor);
        bool is_long_castle_possible(PieceColor playerColor);

        bool is_beaten(Point square, PieceColor attackerColor);
        bool is_beaten_by_pawn(Point square, PieceColor attackerColor);
        bool is_beaten_by_knight(Point square, PieceColor attackerColor);

        Piece& get_piece(Point square);
        Piece get_piece(Point square) const;
        void set_piece(Point square, Piece);
};

void print_chessposition(const ChessPosition& pos, bool verbose = false);