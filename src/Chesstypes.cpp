#include "Chesstypes.h"
#include <string>
#include <vector>
#include <iostream>

PieceColor getOppositeColor(PieceColor color) {
    if (color == PieceColor::BLACK) return PieceColor::WHITE;
    if (color == PieceColor::WHITE) return PieceColor::BLACK;
    return PieceColor::EMPTY;
}

bool Piece::is_white() const {
    return color == PieceColor::WHITE;
}
bool Piece::is_black() const {
    return color == PieceColor::BLACK;
}
bool Piece::is_empty() const {
    return color == PieceColor::EMPTY;
}
bool Piece::is_pawn() const {
    return type == PieceType::PAWN;
}
bool Piece::is_rook() const {
    return type == PieceType::ROOK;
}
bool Piece::is_bishop() const {
    return type == PieceType::BISHOP;
}
bool Piece::is_knight() const {
    return type == PieceType::KNIGHT;
}
bool Piece::is_king() const {
    return type == PieceType::KING;
}
bool Piece::is_queen() const {
    return type == PieceType::QUEEN;
}


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


bool Point::is_on_board() const {
    return ( x >= 0 && y >= 0 && x < 8 && y < 8);
}

Point& Point::operator += (Point rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}
Point& Point::operator *= (int num) {
    x *= num;
    y *= num;
    return *this;
}
Point operator + (Point lhs, Point rhs) {
    lhs += rhs;
    return lhs;
}
Point operator * (Point lhs, int num) {
    lhs *= num;
    return lhs;
}
bool Point::operator == (const Point& rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Move::is_on_board() const {
    if (!from.is_on_board() || !to.is_on_board()) {
        return false;
    }
    return true;
}
bool Move::operator == (const Move& rhs) const {
    return (from == rhs.from && to == rhs.to);
}

Move black_castle {{4,7}, {6,7}};
Move white_castle {{4,0}, {6,0}};
Move white_long_castle {{4,0}, {2,0}};
Move black_long_castle {{4,7}, {2,7}};

Move get_castle_move(PieceColor playerColor) {
    return (playerColor == PieceColor::WHITE ? white_castle : black_castle);
}
Move get_long_castle_move(PieceColor playerColor) {
    return (playerColor == PieceColor::WHITE ? white_long_castle : black_long_castle);
}


bool ChessPosition::make_move(PieceColor playerColor, Move move) {
    if (!is_valid_move(move, playerColor)) {
        return false;
    }

    auto moving_piece = get_piece(move.from);

    if (moving_piece.is_king() && moving_piece.is_white()) {
        IS_WHITE_CASTLE_POSSIBLE = false;
        IS_WHITE_LONG_CASTLE_POSSIBLE = false;
        whiteKingPos = move.to;

        if (move == Move{{4,0}, {6,0}}) {
            set_piece({4,0}, E());
            set_piece({5,0}, WR());
            set_piece({6,0}, WK());
            set_piece({7,0}, E());
        }

        if (move == Move{{4,0}, {2,0}}) {
            set_piece({4,0}, E());
            set_piece({3,0}, WR());
            set_piece({2,0}, WK());
            set_piece({0,0}, E());
        }
    }
    if (moving_piece.is_king() && moving_piece.is_black()) {
        IS_BLACK_CASTLE_POSSIBLE = false;
        IS_BLACK_LONG_CASTLE_POSSIBLE = false;
        blackKingPos = move.to;

        if (move == Move{{4,7}, {6,7}}) {
            set_piece({4,7}, E());
            set_piece({5,7}, WR());
            set_piece({6,7}, WK());
            set_piece({7,7}, E());
        }

        if (move == Move{{4,7}, {2,7}}) {
            set_piece({4,7}, E());
            set_piece({3,7}, WR());
            set_piece({2,7}, WK());
            set_piece({0,7}, E());
        }
    }

    if (moving_piece.is_rook()) {
        if (move.from == Point{0,0}) IS_WHITE_LONG_CASTLE_POSSIBLE = false;
        if (move.from == Point{7,0}) IS_WHITE_CASTLE_POSSIBLE = false;
        if (move.from == Point{0,7}) IS_BLACK_LONG_CASTLE_POSSIBLE = false;
        if (move.from == Point{7,7}) IS_BLACK_CASTLE_POSSIBLE = false;
    }

    if (moving_piece.is_pawn() && moving_piece.is_white()) {
        if (move.to.y == 7) {
            NEED_PROMOTION = true;
            promotion_square = move.to;
        }
        if (move.to.x != move.from.x && get_piece(move.to).is_empty()) {
            set_piece(move.to, moving_piece);
            set_piece(move.from, E());
            set_piece(lastMove.to, E());
        } else {
            set_piece(move.to, moving_piece);
            set_piece(move.from, E());
        }
    } 
    else 
    if (moving_piece.is_pawn() && moving_piece.is_black())  {
        if (move.to.y == 0) {
            NEED_PROMOTION = true;
            promotion_square = move.to;
        }
        if (move.to.x != move.from.x  && get_piece(move.to).is_empty()) {
            set_piece(move.to, moving_piece);
            set_piece(move.from, E());
            set_piece(lastMove.to, E());
        } else {
            set_piece(move.to, moving_piece);
            set_piece(move.from, E());
        }
    } 
    else {
        set_piece(move.to, moving_piece);
        set_piece(move.from, E());
    }


    lastMove = move;

    if (!NEED_PROMOTION) {
        ++moveCounter;
        turn = getOppositeColor(playerColor);
    }

    return true;
}
bool ChessPosition::make_promotion(PieceColor playerColor, PieceType newPiece) 
{
    if (playerColor != turn || !NEED_PROMOTION) {
        return false;
    }

    set_piece(promotion_square, {playerColor, newPiece});

    NEED_PROMOTION = false;
    ++moveCounter;
    turn = getOppositeColor(playerColor);

    return true;
}

bool ChessPosition::is_valid_move(Move move, PieceColor playerColor)
{
    if (playerColor != turn || NEED_PROMOTION || !move.is_on_board()) {
        return false;
    }

    auto moving_piece = get_piece(move.from);
    auto valid_moves = get_valid_moves(moving_piece.type, move.from, playerColor);

    for (auto valid_move : valid_moves) {
        if (valid_move == move) {
            return true;
        }
    }

    return false;
}


static const std::vector<Point> white_attack_pawn_moves {{1,1}, {-1,1}};
static const std::vector<Point> black_attack_pawn_moves {{1,-1}, {-1,-1}};
static const Point white_pawn_move {0,1};
static const Point black_pawn_move {0,-1};

Point get_pawn_move(PieceColor playerColor) {
    return (playerColor == PieceColor::WHITE ? white_pawn_move : black_pawn_move);
}
std::vector<Point> get_attack_pawn_moves(PieceColor playerColor) {
    return (playerColor == PieceColor::WHITE ? white_attack_pawn_moves : black_attack_pawn_moves);
}

static const std::vector<Point> knight_moves {{1,2}, {2,1}, {-1,-2}, {-2,-1}, {-1,2}, {2, -1}, {1,-2}, {-2,1}};
static const std::vector<Point> bishop_moves {{1,1}, {-1,-1}, {1,-1}, {-1,1}};
static const std::vector<Point> rook_moves {{1,0}, {-1,0}, {0,1}, {0,-1}};
static const std::vector<Point> king_moves {{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {-1,-1}, {1,-1}, {-1,1}};

static const std::vector<Point> white_castle_squares {{4,0}, {5,0}, {6,0}};
static const std::vector<Point> black_castle_squares {{4,7}, {5,7}, {6,7}};
static const std::vector<Point> white_long_castle_squares {{2,0}, {3,0}, {4,0}};
static const std::vector<Point> black_long_castle_squares {{2,7}, {3,7}, {4,7}};
static const Point white_long_castle_extra_square {1,0};
static const Point black_long_castle_extra_square {1,7};

bool ChessPosition::is_checked(PieceColor playerColor) {
    auto kingpos = (playerColor == PieceColor::WHITE ? whiteKingPos : blackKingPos);
    return is_beaten(kingpos, getOppositeColor(playerColor));
}

bool ChessPosition::is_checkmated(PieceColor playerColor) {
    for (int x = 0; x < 8; ++x)
    for (int y = 0; y < 8; ++y)
    {
        Point point = {x,y};
        auto piece = get_piece(point);

        if (piece.color != playerColor) {
            continue;
        }

        std::vector<Move> moves = get_valid_moves(piece.type, point, playerColor);

        if (!moves.empty()) {
            return false;
        }
    }

    return true;
}

std::vector<Move> ChessPosition::get_valid_moves(PieceType type, Point point, PieceColor playerColor) {
    std::vector<Move> moves;
    
    switch (type) {
        case PieceType::PAWN :
            moves = get_valid_pawn_moves(point, playerColor);
            break;
        case PieceType::ROOK :
            moves = get_valid_rook_moves(point, playerColor);
            break;
        case PieceType::KNIGHT :
            moves = get_valid_knight_moves(point, playerColor);
            break;
        case PieceType::BISHOP :
            moves = get_valid_bishop_moves(point, playerColor);
            break;
        case PieceType::QUEEN :
            moves = get_valid_queen_moves(point, playerColor);
            break;
        case PieceType::KING :
            moves = get_valid_king_moves(point, playerColor);
            break;
    }

    return moves;
}

std::vector<Move> ChessPosition::get_valid_pawn_moves(Point from, PieceColor playerColor) {
    std::vector<Move> out;

    for (int len = 1; len <= 2; ++len)
    {
        auto pawn_move = get_pawn_move(playerColor);

        auto to = from + (pawn_move * len);

        if (!to.is_on_board()) {
            break;
        }

        if (len == 2) {
            if (PieceColor::WHITE == playerColor && from.y != 1) break;
            if (PieceColor::BLACK == playerColor && from.y != 6) break;
        }

        auto targetPiece = get_piece(to);
        if (!targetPiece.is_empty()) {
            break;
        }

        Move move = {from,to};

        if (!is_prohibited_move(move, playerColor)) {
            out.push_back(move);
        }
    }

    for (auto attack_pawn_move : get_attack_pawn_moves(playerColor))
    {
        auto to = from + attack_pawn_move;
        if (!to.is_on_board()) {
            break;
        }

        auto targetPiece = get_piece(to);

        bool passant_checker = targetPiece.is_empty() && is_passant_square(to, playerColor);
        bool capture_checker = targetPiece.color == getOppositeColor(playerColor);

        if (!passant_checker && !capture_checker) {
            continue;
        }

        Move move = {from,to};

        if (passant_checker) {
            auto piece_from = get_piece(from);
            auto piece_lastmove_to = get_piece(lastMove.to);

            set_piece(to, piece_from);
            set_piece(from, E());
            set_piece(lastMove.to, E());

            if (!is_checked(playerColor)) {
                out.push_back(move);
            }

            set_piece(to, E());
            set_piece(from, piece_from);
            set_piece(lastMove.to, piece_lastmove_to);

        } else if (!is_prohibited_move(move, playerColor)) {
            out.push_back(move);
        }
    }

    return out;
}
std::vector<Move> ChessPosition::get_valid_rook_moves(Point from, PieceColor playerColor) {
    std::vector<Move> out;

    for (auto rook_move : rook_moves)
    for (int len = 1; len <= 8; ++len)
    {
        auto to = from + (rook_move * len);
        if (!to.is_on_board()) {
            break;
        }

        auto targetPiece = get_piece(to);

        if (targetPiece.color == playerColor) {
            break;
        }

        Move move = {from, to};
        
        if (!is_prohibited_move(move, playerColor)) {
            out.push_back(move);
        }
    }

    return out;
}
std::vector<Move> ChessPosition::get_valid_knight_moves(Point from, PieceColor playerColor) {
    std::vector<Move> out;

    for (auto knight_move : knight_moves)
    {
        auto to = from + knight_move;
        if (!to.is_on_board()) {
            continue;
        }

        auto targetPiece = get_piece(to);

        if (targetPiece.color == playerColor) {
            continue;
        }

        Move move = {from, to};
        
        if (!is_prohibited_move(move, playerColor)) {
            out.push_back(move);
        }
    }

    return out;
}
std::vector<Move> ChessPosition::get_valid_bishop_moves(Point from, PieceColor playerColor) {
    std::vector<Move> out;

    for (auto bishop_move : bishop_moves)
    for (int len = 1; len <= 8; ++len)
    {
        auto to = from + (bishop_move * len);
        if (!to.is_on_board()) {
            break;
        }

        auto targetPiece = get_piece(to);

        if (targetPiece.color == playerColor) {
            break;
        }

        Move move = {from, to};
        
        if (!is_prohibited_move(move, playerColor)) {
            out.push_back(move);
        }
    }

    return out;
}
std::vector<Move> ChessPosition::get_valid_queen_moves(Point from, PieceColor playerColor) {
    std::vector<Move> out;

    for (auto queen_move : king_moves)
    for (int len = 1; len <= 8; ++len)
    {
        auto to = from + (queen_move * len);
        if (!to.is_on_board()) {
            break;
        }

        auto targetPiece = get_piece(to);

        if (targetPiece.color == playerColor) {
            break;
        }

        Move move = {from, to};
        
        if (!is_prohibited_move(move, playerColor)) {
            out.push_back(move);
        }
    }

    return out;
}
std::vector<Move> ChessPosition::get_valid_king_moves(Point from, PieceColor playerColor) {
    std::vector<Move> out;

    for (auto king_move : king_moves)
    {
        auto to = from + king_move;
        if (!to.is_on_board()) {
            continue;
        }

        auto targetPiece = get_piece(to);

        if (targetPiece.color == playerColor) {
            continue;
        }

        Move move = {from, to};
        
        if (!is_prohibited_move(move, playerColor)) {
            out.push_back(move);
        }
    }

    if (is_castle_possible(playerColor)) {
        out.push_back(get_castle_move(playerColor));
    }

    if (is_long_castle_possible(playerColor)) {
        out.push_back(get_long_castle_move(playerColor));
    }

    return out;
}

bool ChessPosition::is_passant_square(Point square, PieceColor playerColor) {
    Move rightLastMove;

    if (playerColor == PieceColor::WHITE) {
        rightLastMove = {{square.x, square.y+1}, {square.x, square.y-1}};
    }
    if (playerColor == PieceColor::BLACK) {
        rightLastMove = {{square.x, square.y-1}, {square.x, square.y+1}};
    }

    auto lastPiece = get_piece(rightLastMove.to);

    if (lastPiece.color != playerColor && lastPiece.is_pawn() && lastMove == rightLastMove) {
        return true;
    }

    return false;
}


bool ChessPosition::is_prohibited_move(Move move, PieceColor playerColor) {

    auto piece_to = get_piece(move.to);
    auto piece_from = get_piece(move.from);

    set_piece(move.to, piece_from);
    set_piece(move.from, E());

    bool out = is_checked(playerColor);

    set_piece(move.to, piece_to);
    set_piece(move.from, piece_from);

    return out;
}

bool ChessPosition::is_castle_possible(PieceColor playerColor) {
    bool flag = (playerColor == PieceColor::WHITE ? IS_WHITE_CASTLE_POSSIBLE : IS_BLACK_CASTLE_POSSIBLE);
    if (!flag) return false;

    auto targetSquares = (playerColor == PieceColor::WHITE ? white_castle_squares : black_castle_squares);
    auto enemyColor = getOppositeColor(playerColor);

    for (auto targetSquare : targetSquares) 
    {
        auto piece = get_piece(targetSquare);

        bool piece_checker = piece.is_empty() || (piece.is_king() && piece.color == playerColor);

        if (!piece_checker) return false;
        if (is_beaten(targetSquare, enemyColor)) return false;
    }
    
    return true;
}
bool ChessPosition::is_long_castle_possible(PieceColor playerColor) {
    bool flag = (playerColor == PieceColor::WHITE ? IS_WHITE_LONG_CASTLE_POSSIBLE : IS_BLACK_LONG_CASTLE_POSSIBLE);
    if (!flag) return false;

    auto targetSquares = (playerColor == PieceColor::WHITE ? white_long_castle_squares : black_long_castle_squares);
    auto enemyColor = getOppositeColor(playerColor);

    for (auto targetSquare : targetSquares) 
    {
        auto piece = get_piece(targetSquare);

        bool piece_checker = piece.is_empty() || (piece.is_king() && piece.color == playerColor);

        if (!piece_checker) return false;
        if (is_beaten(targetSquare, enemyColor)) return false;
    }
    
    auto extra_square = (playerColor == PieceColor::WHITE ? white_long_castle_extra_square : black_long_castle_extra_square);
    auto piece = get_piece(extra_square);
    if (!piece.is_empty()) return false;

    return true;
}


bool ChessPosition::is_beaten(Point square, PieceColor attackerColor) {

    for (auto move : rook_moves) 
    for (int len = 1; len <= 8; ++len) 
    {
        auto targetSquare = square + (move * len);
        if (!targetSquare.is_on_board()) {
            break;
        }

        auto targetPiece = get_piece(targetSquare);

        if (targetPiece.color != attackerColor) {
            break;
        }

        bool type_check = targetPiece.is_rook() || targetPiece.is_queen() ||
                          (len == 1 && targetPiece.is_king());

        bool color_check = targetPiece.color == attackerColor;    
            
        if (type_check && color_check) {
            return true;
        }
    }

    for (auto move : bishop_moves) 
    for (int len = 1; len <= 8; ++len) 
    {
        auto targetSquare = square + (move * len);
        if (!targetSquare.is_on_board()) {
            break;
        }

        auto targetPiece = get_piece(targetSquare);

        if (targetPiece.color != attackerColor) {
            break;
        }

        bool type_check = targetPiece.is_bishop() || targetPiece.is_queen() ||
                    (len == 1 && targetPiece.is_king());
                    
        bool color_check = targetPiece.color == attackerColor;    
            
        if (type_check && color_check) {
            return true;
        }
    }

    if (is_beaten_by_knight(square, attackerColor)) {
        return true;
    }

    if (is_beaten_by_pawn(square, attackerColor)) {
        return true;
    }

    return false;
}

bool ChessPosition::is_beaten_by_pawn(Point square, PieceColor attackerColor) {
    
    auto pawn_moves = (attackerColor == PieceColor::WHITE ? black_attack_pawn_moves : white_attack_pawn_moves);

    for (auto pawn_move : pawn_moves)
    {
        auto targetSquare = square + pawn_move;

        if (!targetSquare.is_on_board()) {
            continue;
        }

        auto targetPiece = get_piece(targetSquare);

        if (targetPiece.is_pawn() && targetPiece.color == attackerColor) {
            return true;
        }
    }

    return false;
}

bool ChessPosition::is_beaten_by_knight(Point square, PieceColor attackerColor) {
    for (auto knight_move : knight_moves) 
    {
        auto targetSquare = square + knight_move;

        if (!targetSquare.is_on_board()) {
            continue;
        }

        auto targetPiece = get_piece(targetSquare);
        
        if (targetPiece.is_knight() && targetPiece.color == attackerColor) {
            return true;
        }
    }
    return false;
}


Piece& ChessPosition::get_piece(Point square) {
    return board[square.x][square.y];
}
Piece ChessPosition::get_piece(Point square) const {
    return board[square.x][square.y];
}
void ChessPosition::set_piece(Point square, Piece new_piece) {
    board[square.x][square.y] = new_piece;
}


void print_chessposition(const ChessPosition& pos, bool verbose) {
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

        std::cout << "white king pos: {" << pos.whiteKingPos.x << "," << pos.whiteKingPos.y << "}\n";
        std::cout << "black king pos: {" << pos.blackKingPos.x << "," << pos.blackKingPos.y << "}\n";
        std::cout << "need promotion : " << (pos.NEED_PROMOTION ? "true" : "false") << "\n";
        std::cout << "promotion square: {" << pos.promotion_square.x << "," << pos.promotion_square.y << "}\n";

    }

}