#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"
using namespace sf;

class Game
{
public:
    Game();
    bool isWindowOpen();
    bool isRunning() const;
    void update(Time time);
    void render();
    void run();
    void updateButtonPositions();
    void handleStartButtonClick();
    void setupButtons();
    void setupLevelButtons();
    void setupMultiplayerButton();
    void handleMultiplayerButtonClick();

private:
    bool gameStarted;
    bool levelSelected;
    bool multiplayerMode;
    void resetGame();
    void updatelifeText();
    void updatescore();
    // for highscore
    void loadHighscore();
    void saveHighscore();
    void updateHighscore();
    void handleLevelSelection();

    RenderWindow game_window;
    Color game_backgroundColor;
    Color game_paddleColor;
    Color game_ballColor;
    RectangleShape game_playerPaddle;
    RectangleShape game_cpuPaddle;
    CircleShape game_ball;

    float game_ballVelocityX; // it has two public members x and y , they are the component of 2D vector
    float game_ballVelocityY; // it has two public members x and y , they are the component of 2D vector
    float game_paddleVelocity;
    int life;
    int game_highscore;
    int game_score;
    int varCpuVelocity;
    int ballVeloX;
    int ballVeloY;
    int windowWidth; // Default width
    int windowHeight; // Default height
    int buttonWidth;
    int buttonHeight;
    int buttonSpacing;
    int buttonPosX;
    int buttonPosY;
    int startY;

    Font game_font;
    Text game_lifetext;
    Text game_highscoretext;
    Text game_scoretext;

    Clock game_clock;
    Button closeBtn;
    Button restartBtn;
    Button startBtn;
    Button level1;
    Button level2;
    Button level3;
    Button multiplayer;
};
