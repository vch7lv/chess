#include "Player.h"
#include "GameException.h"

std::shared_ptr<Player> Player::get_instance()
{
    return std::make_shared<Player>();
}

bool Player::make_move(Move move)
{
    if (!game) return false;

    return game->make_move(shared_from_this(), move);
}

bool Player::make_promotion(PieceType newPieceType)
{
    if (!game) return false;

    return game->make_promotion(shared_from_this(), newPieceType);
}

const ChessPosition& Player::get_position() const
{
    if (!game)
    {
        GameException e("try call Player::get_ChessGameInfo(), when Player::game is nullptr");
        throw(e);
    }

    return game->get_position();
}

void Player::add_game(std::shared_ptr<Game> new_game)
{
    game = new_game;
}

void Player::leave_game()
{
    game = nullptr;
}