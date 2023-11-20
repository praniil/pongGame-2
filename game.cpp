#include <SFML/Graphics.hpp>
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
    game_playerPaddle.setSize(Vector2f(25, 75));
    game_cpuPaddle.setSize(Vector2f(25, 75));
    game_ball.setRadius(15);
    int windowWidth = 1280; // Default width
    int windowHeight = 800; // Default height
    // game_ballVelocityX = 450;
    // game_ballVelocityY = 450;
    game_paddleVelocity = 7;
    game_score = -1;
    life = 2;
    game_highscore = 0;

    // game window
    game_window.create(VideoMode(1280, 800), "Pong Game");

    VideoMode screenResolution = VideoMode ::getDesktopMode();
    float centerX = (static_cast<float>(screenResolution.width) - game_window.getSize().x) / 2;
    float centerY = (static_cast<float>(screenResolution.height) - game_window.getSize().y) / 2;

    game_window.create(sf::VideoMode(1280, 800), "Pong Game");
    game_window.setPosition(sf::Vector2i(static_cast<int>(centerX), static_cast<int>(centerY)));
    // setting up player paddle
    game_playerPaddle.setFillColor(game_paddleColor);
    game_playerPaddle.setPosition(10.f, game_window.getSize().y / 2 - game_playerPaddle.getSize().y / 2);
    // setting up cpu paddle
    game_cpuPaddle.setFillColor(game_paddleColor);
    game_cpuPaddle.setPosition(game_window.getSize().x - 35.f, game_window.getSize().y / 2 - game_cpuPaddle.getSize().y / 2);
    // setting up pong ball
    game_ball.setFillColor(game_ballColor);
    game_ball.setPosition(game_window.getSize().x / 2 - game_ball.getRadius(), game_window.getSize().y / 2 - game_ball.getRadius());

    // font
    game_font.loadFromFile("arial.ttf");

    // life
    game_lifetext.setFont(game_font);
    game_lifetext.setCharacterSize(36);
    game_lifetext.setFillColor(Color ::Green);

    game_lifetext.setPosition(game_window.getSize().x / 2, 10.f);
    game_lifetext.setString("Life: " + to_string(life));

    // highscore
    game_highscoretext.setFont(game_font);
    game_highscoretext.setCharacterSize(36);
    game_highscoretext.setFillColor(Color::Cyan);
    game_highscoretext.setPosition(20.f, 10.f);

    // gameScore
    game_scoretext.setFont(game_font);
    game_scoretext.setCharacterSize(36);
    game_scoretext.setFillColor(Color::Cyan);
    game_scoretext.setPosition(game_window.getSize().x / 2 + game_window.getSize().x / 4, 10.f);
    // game_scoretext.setString("Score: " + to_string(game_score));
    gameStarted = false;
    levelSelected = false;
    setupButtons();
    loadHighscore();
    // updateHighscore();
}

// close and restart buttons
bool Game::isRunning() const
{
    return game_window.isOpen();
}
bool Game::isWindowOpen()
{
    return game_window.isOpen();
}

// start button
void Game::setupButtons()
{
    updateButtonPositions();
    startBtn.setButton(buttonPosX, buttonPosY, buttonWidth, buttonHeight, "Start", game_font, [this]()
                       { gameStarted = true; });
}

void Game::setupLevelButtons()
{
    updateButtonPositions();
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
}

void Game::updateButtonPositions()
{
    windowWidth = game_window.getSize().x;
    windowHeight = game_window.getSize().y;

    buttonWidth = windowWidth / 8;
    buttonHeight = windowHeight / 16;
    buttonSpacing = windowHeight / 24;

    buttonPosX = windowWidth / 10;
    buttonPosY = windowHeight / 4;
    startY = windowHeight / 3;
}

void Game::handleLevelSelection()
{
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
            if (event.type == sf::Event::Resized)
            {
                updateButtonPositions();
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
                        varCpuVelocity = 450;
                        ballVeloX = 450;
                        ballVeloY = 450;
                    }
                    if (level2.isButtonClicked(mousePosition))
                    {
                        levelSelected = true;
                        varCpuVelocity = 700;
                        ballVeloX = 550;
                        ballVeloY = 550;
                    }
                    if (level3.isButtonClicked(mousePosition))
                    {
                        levelSelected = true;
                        varCpuVelocity = 900;
                        ballVeloX = 660;
                        ballVeloY = 660;
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
void Game ::handleStartButtonClick()
{
    Vector2f mosePosition = Vector2f(Mouse::getPosition(game_window));
    if (startBtn.isButtonClicked(mosePosition))
    {
        gameStarted = false;
        setupLevelButtons();
    }
}
void Game::run()
{
    setupButtons();
    setupLevelButtons();
    gameStarted = false;
    levelSelected = false;

    while (game_window.isOpen())
    {
        sf::Event event;
        while (game_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                game_window.close();
            }
            if (event.type == sf::Event::Resized)
            {
                updateButtonPositions();
            }
            if (!gameStarted)
            {
                sf::Vector2f mousePosition = game_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                if (startBtn.isButtonClicked(mousePosition) && event.type == sf::Event::MouseButtonReleased)
                {

                    gameStarted = true;
                    levelSelected = false;
                }
            }
        }
        game_window.clear(Color::Black);
        if (gameStarted && !levelSelected)
        {
            handleLevelSelection();

            levelSelected = true;
        }
        if (!levelSelected)
        {
            setupButtons();
            setupLevelButtons();
            level1.drawButton(game_window);
            level2.drawButton(game_window);
            level3.drawButton(game_window);
        }
        if (gameStarted && levelSelected)
        {

            if (life <= 0)
            {
                resetGame();
                game_window.clear(Color::Black);
                break;
            }
            game_window.draw(game_cpuPaddle);
            Time time = game_clock.restart();
            render();
            update(time); // Update game logic
            updateHighscore();
        }
        else
        {
            startBtn.draw(game_window);
        }

        game_window.display();
    }
}

void Game ::resetGame()
{
    game_score = -1;
    life = 2;
    updatelifeText();
    // updatescore();
    game_window.draw(game_cpuPaddle);
    game_cpuPaddle.setPosition(game_window.getSize().x - 35.f, game_window.getSize().y / 2 - game_cpuPaddle.getSize().y / 2);
    game_playerPaddle.setPosition(10.f, game_window.getSize().y / 2 - game_playerPaddle.getSize().y / 2);
    cout << (game_cpuPaddle.getPosition().x, game_cpuPaddle.getPosition().y);

    game_ball.setPosition(game_window.getSize().x / 2 - game_ball.getRadius(), game_window.getSize().y / 2 - game_ball.getRadius());
}
void Game::update(Time time)
{
    // player paddle movement;
    if (Keyboard::isKeyPressed(Keyboard::Up) && game_playerPaddle.getPosition().y > 0)
    {
        game_playerPaddle.move(0, -700 * time.asSeconds());
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && game_playerPaddle.getPosition().y < game_window.getSize().y - game_playerPaddle.getSize().y)
    {
        game_playerPaddle.move(0, 700 * time.asSeconds());
    }
    game_ball.move(ballVeloX * time.asSeconds(), ballVeloY * time.asSeconds());

    // cpu paddle movement;
    if (game_ball.getPosition().y > game_cpuPaddle.getPosition().y)
    {
        game_cpuPaddle.move(0, varCpuVelocity * (time.asSeconds() / 1.5));
    }
    else
    {
        game_cpuPaddle.move(0, -varCpuVelocity * (time.asSeconds() * 2));
    }

    // Check collision with paddle
    if (game_ball.getGlobalBounds().intersects(game_playerPaddle.getGlobalBounds()))
    {
        game_ball.move(-ballVeloX * time.asSeconds(), -ballVeloY * time.asSeconds());
        ballVeloX *= -1;
    }
    if (game_ball.getGlobalBounds().intersects(game_cpuPaddle.getGlobalBounds()))
    {
        game_ball.move(-ballVeloX * time.asSeconds(), -ballVeloY * time.asSeconds());
        ballVeloX *= -1;
    }

    // Check for collision with top wall
    if (game_ball.getPosition().y < 0)
    {
        game_ball.move(ballVeloX * time.asSeconds(), -ballVeloY * time.asSeconds());
        ballVeloY *= -1;
    }

    // Check for collision with bottom wall
    if (game_window.getSize().y > 800)
    {
        if (game_ball.getPosition().y > game_window.getSize().y - game_ball.getRadius() * 15)
        {
            game_ball.move(ballVeloX * time.asSeconds(), -ballVeloY * time.asSeconds());
            ballVeloY *= -1;
        }
    }
    else
    {

        if (game_ball.getPosition().y > game_window.getSize().y - game_ball.getRadius() * 2)
        {
            game_ball.move(ballVeloX * time.asSeconds(), -ballVeloY * time.asSeconds());
            ballVeloY *= -1;
        }
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

    if (game_window.getSize().x > 1280)
    {
        if (game_ball.getPosition().x > game_window.getSize().x - game_window.getSize().x / 3 - game_ball.getRadius() - 2.f)
        {
            // Ball hit the right wall, reset its position and reverse the horizontal velocity
            if (life > 0)
            {
                game_score += 1;
                updatescore();
            }

            game_ball.setPosition(game_window.getSize().x / 2 - game_window.getSize().x / 5, game_window.getSize().y / 2 - game_window.getSize().y / 5);
            ballVeloX *= -1;
            updateHighscore();
        }
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

void Game::render()
{
    game_window.clear(game_backgroundColor);
    game_window.draw(game_playerPaddle);
    game_window.draw(game_cpuPaddle);
    game_window.draw(game_ball);
    game_window.draw(game_lifetext);
    game_window.draw(game_scoretext);
    game_scoretext.setString("Score: " + to_string(game_score));
    // updatescore();
    game_highscoretext.setString("High Score: " + to_string(game_highscore));
    game_window.draw(game_highscoretext);

    game_window.display();
}
