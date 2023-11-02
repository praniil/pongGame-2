#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Game
{
public:
    Game();
    void run();
private:
    void resetGame();
    void render();
    void update(Time time);
    void updateLifeText();

    RenderWindow game_window;
    Color game_backgroundColor;
    Color game_paddleColor;
    Color game_ballColor;
    RectangleShape game_playerPaddle;
    RectangleShape game_cpuPaddle;
    CircleShape game_ball;
    float game_ballVelocityX;     //it has two public members x and y , they are the component of 2D vector
    float game_ballVelocityY;     //it has two public members x and y , they are the component of 2D vector
    float game_paddleVelocity;
    int life;
    Font game_font;
    Text game_lifetext;

    Clock game_clock;
};
