#pragma once
#include "ChessTypes.h"
#include <memory>
#include "Game.h"

struct Player : std::enable_shared_from_this<Player>
{
    public:
        static std::shared_ptr<Player> get_instance();

        bool make_move(Move move);
        bool make_promotion(PieceType newPieceType);

        const ChessPosition& get_position() const;

        void add_game(std::shared_ptr<Game> game);
        void leave_game();

    private:

        std::shared_ptr<Game> game {nullptr};
};