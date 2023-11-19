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
        // game.handleEvents(); // Handle game events (including button clicks)x
        // game.handleStartButtonClick();
        // game.update(deltaTime);       // Update game logic
        // game.render();       // Render game elements
        game.run();
    }

    return 0;
}
