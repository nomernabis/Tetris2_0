//
// Created by pavel on 16.02.18.
//

#include <iostream>
#include "Game.h"

Game::Game()
        :m_renderWindow(sf::VideoMode(250, 500), "Tetris"), tetromino(m_shapeManager){

    Shape m_i_shape(i_body),
            m_l_shape(l_body),
            m_z_shape(z_body),
            m_t_shape(t_body),
            m_o_shape(o_body);

    m_shapeManager.add(Type::I, m_i_shape);
    m_shapeManager.add(Type::L, m_l_shape);
    m_shapeManager.add(Type::Z, m_z_shape);
    m_shapeManager.add(Type::T, m_t_shape);
    m_shapeManager.add(Type::O, m_o_shape);

    m_renderWindow.setFramerateLimit(60);

    m_cell.setSize({25, 25});
    m_cell.setFillColor(sf::Color::Black);

    tetromino.set_type(Type::I);
}

void Game::run() {
    while(m_renderWindow.isOpen()){
        readInput();
        update();
        draw();
    }
}

void Game::readInput() {
    sf::Event event;
    while (m_renderWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            m_renderWindow.close();
        }
        if(event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::Left:
                    dx = -1;
                    break;
                case sf::Keyboard::Right:
                    dx = 1;
                    break;
                case sf::Keyboard::Down:
                    dy = 1;
                    break;
                case sf::Keyboard::Up:
                    is_rotate_clicked = true;
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::update() {
    tetromino.clear(map);
    if(dx || dy){
        tetromino.move(dx, dy, map);
    }
    if(is_rotate_clicked){
        tetromino.rotate(map);
    }
    tetromino.draw(map);
    dx = 0, dy = 0;
    is_rotate_clicked = false;
}

void Game::draw() {
    m_renderWindow.clear(sf::Color::White);

    for(int i=0; i < H; ++i){
        for(int j=0; j < W; ++j){
            if(map[i][j] != 0){
                m_cell.setPosition(25 * j, 25 * i);
                m_renderWindow.draw(m_cell);
            }
        }
    }
    m_renderWindow.display();
}