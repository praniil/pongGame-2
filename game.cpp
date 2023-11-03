#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
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
    game_ball.setRadius(25);
    game_ballVelocityX = 450;
    game_ballVelocityY = 450;
    game_paddleVelocity = 7;
    life = 2;
    game_highscore = 0;

    // game window
    game_window.create(VideoMode(1280, 800), "Pong Game");
    // setting up player paddle
    game_playerPaddle.setFillColor(game_paddleColor);
    game_playerPaddle.setPosition(10.f, game_window.getSize().y / 2 - game_playerPaddle.getSize().y / 2);
    // setting up cpu paddle
    game_cpuPaddle.setFillColor(game_paddleColor);
    game_cpuPaddle.setPosition(game_window.getSize().x - 35.f, game_window.getSize().y / 2 - game_playerPaddle.getSize().y / 2);
    // setting up pong ball
    game_ball.setFillColor(game_ballColor);
    game_ball.setPosition(game_window.getSize().x / 2, game_window.getSize().y / 2);

    VideoMode screenResolution = VideoMode ::getDesktopMode();
    float centerX = (static_cast<float>(screenResolution.width) - game_window.getSize().x) / 2;
    float centerY = (static_cast<float>(screenResolution.height) - game_window.getSize().y) / 2;

    game_window.create(sf::VideoMode(1280, 800), "Pong Game");
    game_window.setPosition(sf::Vector2i(static_cast<int>(centerX), static_cast<int>(centerY)));

    // font
    game_font.loadFromFile("arial.ttf");

    // life
    game_lifetext.setFont(game_font);
    game_lifetext.setCharacterSize(36);
    game_lifetext.setFillColor(Color ::Green);
    // if (game_window.getSize().x > 1280)
    // {
    //     game_lifetext.setPosition(game_window.getSize().x / 2, 10.f);
    // }
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
    game_scoretext.setPosition(game_window.getSize().x / 2 + game_window.getSize().x / 4 , 10.f);
    game_scoretext.setString("Score: " + to_string(game_score));
}

void Game ::run()
{
    while (game_window.isOpen())
    {
        Event event;
        while (game_window.pollEvent(event))
        {
            if (event.type == Event ::Closed)
            {
                game_window.close();
            }
        }
        Time time = game_clock.restart();
        update(time);
        render();
    }
}

void Game ::resetGame()
{
    game_score = 0;
    life = 2;
    updatelifeText();
    updatescore();
    game_cpuPaddle.setPosition(game_window.getSize().x - 35.f, game_window.getSize().y / 2 - game_playerPaddle.getSize().y / 2);
    game_playerPaddle.setPosition(10.f, game_window.getSize().y / 2 - game_playerPaddle.getSize().y / 2);
    game_ball.setPosition(game_window.getSize().x / 2, game_window.getSize().y / 2);
}
void Game::update(sf::Time time)
{
    // player paddle movement;
    if (Keyboard::isKeyPressed(Keyboard::Up) && game_playerPaddle.getPosition().y > 0)
    {
        game_playerPaddle.move(0, -450 * time.asSeconds());
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && game_playerPaddle.getPosition().y < game_window.getSize().y - game_playerPaddle.getSize().y)
    {
        game_playerPaddle.move(0, 450 * time.asSeconds());
    }
    game_ball.move(game_ballVelocityX * time.asSeconds(), game_ballVelocityY * time.asSeconds());

    // Check collision with paddle
    if (game_ball.getGlobalBounds().intersects(game_playerPaddle.getGlobalBounds()))
    {
        game_ball.move(-game_ballVelocityX * time.asSeconds(), -game_ballVelocityY * time.asSeconds());
        game_ballVelocityX *= -1;
    }
    if (game_ball.getGlobalBounds().intersects(game_cpuPaddle.getGlobalBounds()))
    {
        game_ball.move(-game_ballVelocityX * time.asSeconds(), -game_ballVelocityY * time.asSeconds());
        game_ballVelocityX *= -1;
    }

    // Check for collision with top wall
    if (game_ball.getPosition().y < 0)
    {
        game_ball.move(game_ballVelocityX * time.asSeconds(), -game_ballVelocityY * time.asSeconds());
        game_ballVelocityY *= -1;
    }

    // Check for collision with bottom wall
    if (game_window.getSize().y > 800)
    {
        if (game_ball.getPosition().y > game_window.getSize().y - game_ball.getRadius() * 9)
        {
            game_ball.move(game_ballVelocityX * time.asSeconds(), -game_ballVelocityY * time.asSeconds());
            game_ballVelocityY *= -1;
        }
    }
    else
    {

        if (game_ball.getPosition().y > game_window.getSize().y - game_ball.getRadius() * 2)
        {
            game_ball.move(game_ballVelocityX * time.asSeconds(), -game_ballVelocityY * time.asSeconds());
            game_ballVelocityY *= -1;
        }
    }

    // cpu paddle movement;
    if (game_ball.getPosition().y > game_cpuPaddle.getPosition().y)
    {
        game_cpuPaddle.move(0, 5 * time.asSeconds());
    }
    else
    {
        game_cpuPaddle.move(0, -5 * time.asSeconds());
    }

    // if it touches the left or right of the screen
    if (game_ball.getPosition().x < 0)
    {
        // Ball hit the left wall, reset its position and reverse the horizontal velocity
        life = life - 1;
        updatelifeText();
        if (life <= 0)
        {
            resetGame();
            game_window.clear(Color ::Black);
        }
        game_ball.setPosition(game_window.getSize().x / 2 - game_ball.getRadius(), game_window.getSize().y / 2 - game_ball.getRadius());
        game_ballVelocityX *= -1;
    }
    if (game_ball.getPosition().x > game_window.getSize().x - game_ball.getRadius() * 2)
    {
        // Ball hit the right wall, reset its position and reverse the horizontal velocity
        game_score = game_score + 1;
        updatescore();

        game_ball.setPosition(game_window.getSize().x / 2 - game_ball.getRadius(), game_window.getSize().y / 2 - game_ball.getRadius());
        game_ballVelocityX *= -1;
    }
}
void Game ::updatelifeText()
{
    game_lifetext.setString("Life: " + to_string(life));
}

void Game :: updatescore() {
    game_scoretext.setString("Score: " + to_string(game_score));
    
}
void Game ::render()
{
    game_window.clear(game_backgroundColor);
    game_window.draw(game_playerPaddle);
    game_window.draw(game_cpuPaddle);
    game_window.draw(game_ball);
    game_window.draw(game_lifetext);
    game_window.draw(game_scoretext);
    game_window.display();
}
