#pragma once
#include "ChessTypes.h"
#include <memory>

class Player;

class Game
{
    protected:
        Game();
        virtual ~Game();


    public:
        virtual bool make_move(std::shared_ptr<Player> player, Move move) = 0;
        virtual bool make_promotion(std::shared_ptr<Player> player, PieceType newPieceType) = 0;

        virtual const ChessPosition& get_position() const = 0;

        virtual void set_black_player(std::shared_ptr<Player> black_player) = 0;
        virtual void set_white_player(std::shared_ptr<Player> white_player) = 0;

        PieceColor get_color(std::shared_ptr<Player> player) const;


    protected:
        std::weak_ptr<Player> white_player;
        std::weak_ptr<Player> black_player;
};

