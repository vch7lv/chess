#include "ChessTypes.h"
#include "Gui.hpp"

int main()
{
    sf::RenderWindow window{ {900, 800}, "MY GUI" };
    Gui gui(window);

    gui.mainloop();
}