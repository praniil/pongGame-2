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
    void updatelifeText();
    void updatescore();
    //for highscore
    void loadHighscore();
    void saveHighscore();
    void updateHighscore();

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
    int game_highscore;
    int game_score;

    Font game_font;
    Text game_lifetext;
    Text game_highscoretext;
    Text game_scoretext;

    Clock game_clock;
};
