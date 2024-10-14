#pragma once
#include "Game.h"
#include "Player.h"


class LocalGame final : public Game
{
    public:
        static std::shared_ptr<Game> get_instance();
        LocalGame() = default;
        ~LocalGame() = default;
    private:

        virtual bool make_move(std::shared_ptr<Player> player, Move move) override;
        virtual bool make_promotion(std::shared_ptr<Player> player, PieceType newPieceType) override;

        virtual const ChessPosition& get_position() const override;

        virtual void set_black_player(std::shared_ptr<Player> black_player) override;
        virtual void set_white_player(std::shared_ptr<Player> white_player) override;

        ChessPosition pos;
};