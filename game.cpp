#include<SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
using namespace sf;

Game :: Game() {
    game_backgroundColor = Color :: Black;
    game_paddleColor = Color :: Green;
    game_ballColor = Color :: White;
    game_playerPaddle.setSize(Vector2f(25, 75));
    game_cpuPaddle.setSize(Vector2f(25, 75));
    game_ball.setRadius(25);

    //game window
    game_window.create(VideoMode(1280, 800), "Pong Game");
    //setting up player paddle
    game_playerPaddle.setFillColor(game_paddleColor);
    game_playerPaddle.setPosition(10.f, game_window.getSize().y/2 - game_playerPaddle.getSize().y / 2);
    //setting up cpu paddle
    game_cpuPaddle.setFillColor(game_paddleColor);
    game_cpuPaddle.setPosition(game_window.getSize().x - 35.f, game_window.getSize().y/2 - game_playerPaddle.getSize().y / 2);
    //setting up pong ball
    game_ball.setFillColor(game_ballColor);
    game_ball.setPosition(game_window.getSize().x / 2, game_window.getSize().y /2);
}   

void Game :: run() {
    while (game_window.isOpen()) {
        Event event;
        render();
    }
}
void Game :: render() {
    game_window.clear(game_backgroundColor);
    game_window.draw(game_playerPaddle);
    game_window.draw(game_cpuPaddle);
    game_window.draw(game_ball);
    game_window.display();
    
}     

