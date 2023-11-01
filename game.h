#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Game
{
public:
    Game();
    void run();

private:
    void render();

    RenderWindow game_window;
    Color game_backgroundColor;
    Color game_paddleColor;
    Color game_ballColor;
    RectangleShape game_playerPaddle;
    RectangleShape game_cpuPaddle;
    CircleShape game_ball;
    Vector2f game_ballVelocity;     //it has two public members x and y , they are the component of 2D vector
};
