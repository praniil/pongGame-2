#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
using namespace sf;
using namespace std;
#include<string>

class Game
{
public:
    Game();
    bool isWindowOpen();
    bool isRunning() const;
    void update(Time time);
    void render();
    void renderMultiplayer();
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
    void updateScore1();
    void updateScore2();
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
    SoundBuffer soundBuffer;
    Sound sound;

    float game_ballVelocityX; // it has two public members x and y , they are the component of 2D vector
    float game_ballVelocityY; // it has two public members x and y , they are the component of 2D vector
    float game_paddleVelocity;
    int life;
    int game_highscore;
    int game_score;
    int game_score1;
    int game_score2;
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
    string infoMultiplayerString;

    Font game_font;
    Text game_lifetext;
    Text game_highscoretext;
    Text game_scoretext;
    Text game_score1text;
    Text game_score2text;
    Text infoMulitplayer;

    Clock game_clock;
    Button closeBtn;
    Button restartBtn;
    Button startBtn;
    Button level1;
    Button level2;
    Button level3;
    Button multiplayer;
};
