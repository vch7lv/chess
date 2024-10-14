#include "LocalGame.h"

Game::Game() = default;
Game::~Game() = default;

std::shared_ptr<Game> LocalGame::get_instance() 
{
    auto ptr = std::make_shared<LocalGame>();
    return std::static_pointer_cast<Game>(ptr);
}

PieceColor Game::get_color(std::shared_ptr<Player> player) const 
{
    if (!white_player.expired() && player == white_player.lock()) 
    {
        return PieceColor::WHITE;
    }

    if (!black_player.expired() && player == black_player.lock()) 
    {
        return PieceColor::BLACK;
    }

    return PieceColor::EMPTY;
}

bool LocalGame::make_move(std::shared_ptr<Player> player, Move move) 
{
    return pos.make_move(get_color(player), move);
}

bool LocalGame::make_promotion(std::shared_ptr<Player> player, PieceType newPieceType) 
{
    return pos.make_promotion(get_color(player), newPieceType);
}

const ChessPosition& LocalGame::get_position() const 
{
    return pos;
}

void LocalGame::set_black_player(std::shared_ptr<Player> player) 
{
    if (black_player.expired()) 
    {
        black_player = player;
    }
}

void LocalGame::set_white_player(std::shared_ptr<Player> player) 
{
    if (white_player.expired()) 
    {
        white_player = player;
    }
}