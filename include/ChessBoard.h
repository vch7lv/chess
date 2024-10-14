#include "Widget.h"
#include "Player.h"
#include <unordered_map>

class ChessBoard : public Widget
{
    public:
        ChessBoard();

        void set_background_texture(sf::Texture texture);
        void set_piece_texture(Piece piece, sf::Texture texture);
        void set_player(std::shared_ptr<Player> player);

        static std::shared_ptr<ChessBoard> create_ChessBoard();
        
    private:

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void handleEvent(const sf::Event& event) override;


        std::shared_ptr<Player> player;

        PieceColor Side = PieceColor::WHITE;

        bool has_focused_piece = false;
        sf::Vector2f focused_piece_position;
        Point focused_piece;

        sf::Texture background;

        struct piece_cmp;
        std::unordered_map<Piece, sf::Texture, piece_hash> textures;
};

struct piece_hash
{
    std::size_t operator () (const Piece& piece) const;
};