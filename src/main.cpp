#include "Chesstypes.h"

int main()
{
    ChessPosition pos;
    auto col = PieceColor::WHITE;

    print_chessposition(pos);

    while (true) {
        int b,d;
        char a,c;
        std::cin >> a >> b >> c >> d;


        if (pos.make_move(col, {{a-'a',b-1},{c-'a',d-1}})) {
            print_chessposition(pos);
            std::cout << std::endl;
            col = getOppositeColor(col);
        } else {
            std::cout << "bad move" << std::endl;
        }
    }
}