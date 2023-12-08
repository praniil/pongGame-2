#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include "game.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

using namespace sf;
Game ::Game()
{
    game_backgroundColor = Color ::Black;
    game_paddleColor = Color ::White;
    game_ballColor = Color ::White;
    game_playerPaddle.setSize(Vector2f(5, 75));
    game_cpuPaddle.setSize(Vector2f(5, 75));
    game_ball.setRadius(15);
    int windowWidth = 1280; // Default width
    int windowHeight = 800; // Default height
    game_ballVelocityX = 800;
    game_ballVelocityY = 800;
    game_paddleVelocity = 7;
    game_score = 0;
    game_score1 = 0;
    game_score2 = 0;
    life = 3;
    game_highscore = 0;

    // game window

    VideoMode screenResolution = VideoMode ::getDesktopMode();

    game_window.create(VideoMode::getFullscreenModes()[0], "Pong Game");
    game_window.setPosition(Vector2i(0, 0));
    // game_window.setPosition(sf::Vector2i(static_cast<int>(centerX), static_cast<int>(centerY)));
    // setting up player paddle
    game_playerPaddle.setFillColor(game_paddleColor);
    game_playerPaddle.setPosition(20.f, game_window.getSize().y / 2 - game_playerPaddle.getSize().y / 2);
    // setting up cpu paddle
    game_cpuPaddle.setFillColor(game_paddleColor);
    game_cpuPaddle.setPosition(game_window.getSize().x - 25.f, game_window.getSize().y / 2 - game_cpuPaddle.getSize().y / 2);
    // setting up pong ball
    game_ball.setFillColor(game_ballColor);
    game_ball.setPosition(game_window.getSize().x / 2 - game_ball.getRadius(), game_window.getSize().y / 2 - game_ball.getRadius());

    // font
    game_font.loadFromFile("arial.ttf");

    // sound
    soundBuffer.loadFromFile("pongEdited.wav");
    sound.setBuffer(soundBuffer);

    // background
    if (!backgroundTexture.loadFromFile("gameBg.jpg"))
    {
        game_backgroundColor = Color ::Black;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // life
    game_lifetext.setFont(game_font);
    game_lifetext.setCharacterSize(36);
    game_lifetext.setFillColor(Color ::White);

    game_lifetext.setPosition(game_window.getSize().x / 2, 10.f);
    game_lifetext.setString("Life: " + to_string(life));

    // highscore
    game_highscoretext.setFont(game_font);
    game_highscoretext.setCharacterSize(36);
    game_highscoretext.setFillColor(Color::White);
    game_highscoretext.setPosition(20.f, 10.f);

    // gameScore
    game_scoretext.setFont(game_font);
    game_scoretext.setCharacterSize(36);
    game_scoretext.setFillColor(Color::White);
    game_scoretext.setPosition(game_window.getSize().x / 2 + game_window.getSize().x / 4, 10.f);

    // gameScore1
    game_score1text.setFont(game_font);
    game_score1text.setCharacterSize(36);
    game_score1text.setFillColor(Color::Cyan);
    game_score1text.setPosition(20.f, 10.f);

    // gameScore2
    game_score2text.setFont(game_font);
    game_score2text.setCharacterSize(36);
    game_score2text.setFillColor(Color::Cyan);
    game_score2text.setPosition(game_window.getSize().x / 2 + game_window.getSize().x / 4, 10.f);
    // info Multiplayer
    infoMulitplayer.setFont(game_font);
    infoMulitplayer.setCharacterSize(25);
    infoMulitplayer.setFillColor(Color ::White);
    infoMulitplayer.setPosition(game_window.getSize().x / 2 - game_window.getSize().x / 3, game_window.getSize().y - 30.f);

    gameStarted = false;
    levelSelected = false;
    multiplayerMode = false;
    loadHighscore();
    // updateHighscore();
}

bool Game::isRunning() const
{
    return game_window.isOpen();
}
// bool Game::isWindowOpen()
// {
//     return game_window.isOpen();
// }

void Game::setupMultiplayerButton()
{
    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0]; // Get the fullscreen mode
    int windowWidth = fullscreenMode.width;
    int windowHeight = fullscreenMode.height;

    int buttonWidth = windowWidth / 8;
    int buttonHeight = windowHeight / 16;
    int buttonSpacing = windowHeight / 24;

    int buttonPosX = windowWidth / 10;
    int buttonPosY = windowHeight / 4;
    int startY = windowHeight / 3;

    multiplayer.setButton((windowWidth - buttonWidth) / 2, startY + 3 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight, "Multiplayer", game_font, [this]()
                          { multiplayerMode = true; });
}

void Game::setupLevelButtons()
{
    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0]; // Get the fullscreen mode
    int windowWidth = fullscreenMode.width;
    int windowHeight = fullscreenMode.height;

    int buttonWidth = windowWidth / 8;
    int buttonHeight = windowHeight / 16;
    int buttonSpacing = windowHeight / 24;

    int buttonPosX = windowWidth / 10;
    int buttonPosY = windowHeight / 4;
    int startY = windowHeight / 3;

    level1.setButton((windowWidth - buttonWidth) / 2, startY, buttonWidth, buttonHeight, "Level 1", game_font, [this]()
                     {
        varCpuVelocity = 800;
        ballVeloX = 450;
        ballVeloY = 450; });

    level2.setButton((windowWidth - buttonWidth) / 2, startY + buttonHeight + buttonSpacing, buttonWidth, buttonHeight, "Level 2", game_font, [this]()
                     {
        varCpuVelocity = 800;
        ballVeloX = 550;
        ballVeloY = 550; });

    level3.setButton((windowWidth - buttonWidth) / 2, startY + 2 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight, "Level 3", game_font, [this]()
                     {
        varCpuVelocity = 1000;
        ballVeloX = 660;
        ballVeloY = 660; });

    closeButton.setButton((windowWidth - buttonWidth) / 2, startY + 4 * (buttonHeight + buttonSpacing), buttonWidth, buttonHeight, "Close", game_font, [this]()
                          { game_window.close(); });
}
void Game::handleMultiplayerButtonClick()
{
    multiplayerMode = true;
    Time time = game_clock.restart();
    while (multiplayerMode && game_window.isOpen())
    {
        Event event;
        while (game_window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                game_window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    sf::Vector2f mousePosition = game_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    if (multiplayer.isButtonClicked(mousePosition))
                    {
                        multiplayerMode = true;
                    }
                }
            }
        }
        renderMultiplayer();
        update(time);
        game_window.display();
    }
}

void Game::handleLevelSelection()
{
    cout << "level selection clicked" << endl;
    bool levelSelected = false;
    while (game_window.isOpen() && !levelSelected)
    {
        Event event;
        while (game_window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                game_window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    sf::Vector2f mousePosition = game_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    Time time;

                    if (level1.isButtonClicked(mousePosition))
                    {
                        levelSelected = true;
                        varCpuVelocity = 540;
                        ballVeloX = 550;
                        ballVeloY = 550;
                    }
                    if (level2.isButtonClicked(mousePosition))
                    {
                        levelSelected = true;
                        varCpuVelocity = 640;
                        ballVeloX = 650;
                        ballVeloY = 650;
                    }
                    if (level3.isButtonClicked(mousePosition))
                    {
                        levelSelected = true;
                        varCpuVelocity = 800;
                        ballVeloX = 800;
                        ballVeloY = 800;
                    }
                }
            }
        }
    }
    game_window.clear(Color::Black);
    level1.drawButton(game_window);
    level2.drawButton(game_window);
    level3.drawButton(game_window);
    game_window.display();
}

void Game::run()
{
    setupLevelButtons();
    setupMultiplayerButton();
    gameStarted = false;
    levelSelected = false;
    multiplayerMode = false;

    while (game_window.isOpen())
    {
        sf::Event event;
        while (game_window.pollEvent(event))
        {
            // Handle window events
            if (event.type == sf::Event::Closed)
            {
                game_window.close();
            }
            else if (!gameStarted)
            {
                sf::Vector2f mousePosition = game_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                if (multiplayer.isButtonClicked(mousePosition) && event.type == sf::Event::MouseButtonReleased)
                {

                    multiplayerMode = true;
                    handleMultiplayerButtonClick();
                }
                else if (closeButton.isButtonClicked(mousePosition) && event.type == Event::MouseButtonReleased)
                {
                    game_window.close();
                }
                else if (level1.isButtonClicked(mousePosition) && event.type == sf::Event::MouseButtonReleased)
                {
                    gameStarted = true;
                    levelSelected = true;
                    varCpuVelocity = 540;
                    ballVeloX = 550;
                    ballVeloY = 550;
                }
                else if (level2.isButtonClicked(mousePosition) && event.type == sf::Event::MouseButtonReleased)
                {
                    gameStarted = true;
                    levelSelected = true;
                    varCpuVelocity = 640;
                    ballVeloX = 650;
                    ballVeloY = 650;
                }
                else if (level3.isButtonClicked(mousePosition) && event.type == sf::Event::MouseButtonReleased)
                {
                    gameStarted = true;
                    levelSelected = true;
                    varCpuVelocity = 800;
                    ballVeloX = 800;
                    ballVeloY = 800;
                }
            }
        }
        Time time = game_clock.restart();
        if (multiplayerMode)
        {
            if (event.type == Event::Closed)
            {
                game_window.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    sf::Vector2f mousePosition = game_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (multiplayer.isButtonClicked(mousePosition))
                    {
                        multiplayerMode = true;
                    }
                }
            }

            renderMultiplayer();
            update(time);
            game_window.display();
        }
        game_window.clear(Color::Black);

        if (!multiplayerMode || !levelSelected)
        {
            game_window.draw(backgroundSprite);
            level1.drawButton(game_window);
            level2.drawButton(game_window);
            level3.drawButton(game_window);
            multiplayer.drawButton(game_window);
            closeButton.drawButton(game_window);
        }
        if (!multiplayerMode)
        {
            multiplayer.drawButton(game_window);
        }
        else
        {

            renderMultiplayer();
            update(time);
        }
        if (!levelSelected)
        {
            level1.drawButton(game_window);
            level2.drawButton(game_window);
            level3.drawButton(game_window);
        }
        else if (!levelSelected)
        {
            handleLevelSelection();
            levelSelected = true;
        }
        else if (levelSelected)
        {
            if (life <= 0)
            {
                resetGame();
                break;
            }
            game_window.draw(game_cpuPaddle);
            Time time = game_clock.restart();
            render();
            update(time);
            updateHighscore();
        }

        game_window.display();
    }
}

void Game ::resetGame()
{
    game_score = 0;
    game_score1 = 0;
    game_score2 = 0;
    life = 3;
    updatelifeText();
    // updatescore();
    game_window.draw(game_cpuPaddle);
    game_cpuPaddle.setPosition(game_window.getSize().x - 25.f, game_window.getSize().y / 2 - game_cpuPaddle.getSize().y / 2);
    game_playerPaddle.setPosition(20.f, game_window.getSize().y / 2 - game_playerPaddle.getSize().y / 2);

    game_ball.setPosition(game_window.getSize().x / 2 - game_ball.getRadius(), game_window.getSize().y / 2 - game_ball.getRadius());
}
void Game::update(Time time)
{

    if (!multiplayerMode)
    {
        game_ball.move((ballVeloX * 10) * time.asSeconds(), (ballVeloY * 10) * time.asSeconds());
        // AI controls
        if (Keyboard::isKeyPressed(Keyboard::Up) && game_playerPaddle.getPosition().y > 0)
        {
            game_playerPaddle.move(0, -(varCpuVelocity * 10) * time.asSeconds());
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) && game_playerPaddle.getPosition().y < game_window.getSize().y - game_playerPaddle.getSize().y)
        {
            game_playerPaddle.move(0, (varCpuVelocity * 10) * time.asSeconds());
        }
        // cpu paddle movement
        if (game_ball.getPosition().y > game_cpuPaddle.getPosition().y)
        {
            game_cpuPaddle.move(0, (varCpuVelocity * 10) * (time.asSeconds()));
        }
        else
        {
            game_cpuPaddle.move(0, -(varCpuVelocity * 10) * (time.asSeconds()));
        }

        // collision with paddle
        if (game_ball.getGlobalBounds().intersects(game_playerPaddle.getGlobalBounds()))
        {
            sound.play();
            game_ball.move(-ballVeloX * time.asSeconds(), -ballVeloY * time.asSeconds());
            ballVeloX *= -1;
        }
        if (game_ball.getGlobalBounds().intersects(game_cpuPaddle.getGlobalBounds()))
        {
            sound.play();
            game_ball.move(-ballVeloX * time.asSeconds(), -ballVeloY * time.asSeconds());
            ballVeloX *= -1;
        }

        // Check for collision with top wall
        if (game_ball.getPosition().y < 0)
        {
            game_ball.move(ballVeloX * time.asSeconds(), -ballVeloY * time.asSeconds());
            ballVeloY *= -1;
        }

        if (game_ball.getPosition().y > game_window.getSize().y - game_ball.getRadius())
        {
            game_ball.move(ballVeloX * time.asSeconds(), -ballVeloY * time.asSeconds());
            ballVeloY *= -1;
        }

        // if it touches the left or right of the screen
        if (game_ball.getPosition().x < 0)
        {
            // Ball hit the left wall, reset its position and reverse the horizontal velocity
            life = life - 1;
            updatelifeText();
            if (life <= 0)
            {
                render();
                // handleEvents();
                // resetGame();
                game_window.clear(Color ::Black);
            }
            game_ball.setPosition(game_window.getSize().x / 2 - game_ball.getRadius(), game_window.getSize().y / 2 - game_ball.getRadius());
            ballVeloX *= -1;
        }
        if (game_ball.getPosition().x > game_window.getSize().x - game_ball.getRadius() * 2)
        {
            // Ball hit the right wall, reset its position and reverse the horizontal velocity
            if (life > 0)
            {
                game_score += 1;
                updatescore();
            }
            game_ball.setPosition(game_window.getSize().x / 2 - game_ball.getRadius(), game_window.getSize().y / 2 - game_ball.getRadius());
            ballVeloX *= -1;
        }
    }
    else
    {
        if (game_score1 >= 3 || game_score2 >= 3)
        {
            resetGame();
            multiplayerMode = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::W) && game_playerPaddle.getPosition().y > 0)
        {
            game_playerPaddle.move(0, -1200 * time.asSeconds());
        }
        if (Keyboard::isKeyPressed(Keyboard::S) && game_playerPaddle.getPosition().y < game_window.getSize().y - game_playerPaddle.getSize().y)
        {
            game_playerPaddle.move(0, 1200 * time.asSeconds());
        }
        // Player 2 controls: W and S keys
        if (Keyboard::isKeyPressed(Keyboard::Up) && game_cpuPaddle.getPosition().y > 0)
        {
            game_cpuPaddle.move(0, -1200 * time.asSeconds());
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) && game_cpuPaddle.getPosition().y < game_window.getSize().y - game_cpuPaddle.getSize().y)
        {
            game_cpuPaddle.move(0, 1200 * time.asSeconds());
        }
        game_ball.move((game_ballVelocityX * 1.45) * time.asSeconds(), (game_ballVelocityY * 1.45) * time.asSeconds());

        // Check collision with paddle
        if (game_ball.getGlobalBounds().intersects(game_playerPaddle.getGlobalBounds()))
        {
            game_ball.move(-game_ballVelocityX * time.asSeconds(), -game_ballVelocityY * time.asSeconds());
            sound.play();
            game_ballVelocityX *= -1;
        }
        if (game_ball.getGlobalBounds().intersects(game_cpuPaddle.getGlobalBounds()))
        {
            game_ball.move(-game_ballVelocityX * time.asSeconds(), -game_ballVelocityY * time.asSeconds());
            sound.play();
            game_ballVelocityX *= -1;
        }

        // Check for collision with top wall
        if (game_ball.getPosition().y < 0)
        {
            game_ball.move(game_ballVelocityX * time.asSeconds(), -game_ballVelocityY * time.asSeconds());
            game_ballVelocityY *= -1;
        }
        if (game_ball.getPosition().y > game_window.getSize().y - game_ball.getRadius())
        {
            game_ball.move(game_ballVelocityX * time.asSeconds(), -game_ballVelocityY * time.asSeconds());
            game_ballVelocityY *= -1;
        }

        // if it touches the left or right of the screen
        if (game_ball.getPosition().x < 0)
        {
            // Ball hit the left wall, reset its position and reverse the horizontal velocity
            if (game_score2 < 3)
            {
                game_score2 = game_score2 + 1;
                updateScore2();
            }
            else
            {
                resetGame();
                game_window.clear(Color::Black);
            }
            game_ball.setPosition(game_window.getSize().x / 2 - game_ball.getRadius(), game_window.getSize().y / 2 - game_ball.getRadius());
            game_ballVelocityX *= -1;
        }

        if (game_ball.getPosition().x > game_window.getSize().x - game_ball.getRadius() - 2.f)
        {
            if (game_score1 < 3)
            {
                game_score1 = game_score1 + 1;
                updateScore1();
                game_window.clear(Color ::Black);
            }
            else
            {
                resetGame();
                game_window.clear(Color::Black);
            }

            game_ball.setPosition(game_window.getSize().x / 2 - game_ball.getRadius(), game_window.getSize().y / 2 - game_ball.getRadius());
            game_ballVelocityX *= -1;
        }
    }
}
// highscore
void Game ::loadHighscore()
{
    ifstream file("gamehighscore.txt");
    if (file.is_open())
    {
        file >> game_highscore;
        file.close();
    }
}
void Game ::saveHighscore()
{
    ofstream file("gamehighscore.txt");
    if (file.is_open())
    {
        file << game_highscore;
        file.close();
    }
}
void Game ::updateHighscore()
{
    if (game_score > game_highscore)
    {
        game_highscore = game_score;
        saveHighscore();
    }
}
void Game ::updatelifeText()
{
    game_lifetext.setString("Life: " + to_string(life));
}

void Game ::updatescore()
{
    game_scoretext.setString("Score: " + to_string(game_score));
}
void Game ::updateScore1()
{
    game_score1text.setString("Player1: " + to_string(game_score1));
}
void Game ::updateScore2()
{
    game_score1text.setString("Player2: " + to_string(game_score2));
}

void Game::render()
{
    game_window.clear(game_backgroundColor);
    game_window.draw(backgroundSprite);
    game_window.draw(game_playerPaddle);
    game_window.draw(game_cpuPaddle);
    game_window.draw(game_ball);
    game_window.draw(game_lifetext);
    game_window.draw(game_scoretext);
    game_scoretext.setString("Score: " + to_string(game_score));
    // updatescore();
    game_highscoretext.setString("High Score: " + to_string(game_highscore));
    game_window.draw(game_highscoretext);
}
void Game::renderMultiplayer()
{
    game_window.clear(game_backgroundColor);
    game_window.draw(backgroundSprite);
    game_window.draw(game_playerPaddle);
    game_window.draw(game_cpuPaddle);
    game_window.draw(game_ball);
    game_window.draw(game_score1text);
    game_window.draw(game_score2text);
    game_window.draw(infoMulitplayer);
    infoMulitplayer.setString("Who ever gets the quickest 3 scores wins!");
    game_score1text.setString("Player1: " + to_string(game_score1));
    game_score2text.setString("Player2: " + to_string(game_score2));
    game_window.display();
}
