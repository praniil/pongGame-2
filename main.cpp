#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>

int main()
{
    Game game;
    sf::Clock clock;
    game.setupButtons();

    while (game.isRunning())
    {
        sf::Time deltaTime = clock.restart();
        game.run();
    }

    return 0;
}
