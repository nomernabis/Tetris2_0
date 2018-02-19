//
// Created by pavel on 16.02.18.
//

#ifndef TETRIS2_0_GAME_H
#define TETRIS2_0_GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "shapes.h"
#include "ShapeManager.h"
#include "Tetromino.h"

class Game {
    sf::RenderWindow m_renderWindow;
    sf::RectangleShape m_cell;
    int map[H][W] = {};
    ShapeManager m_shapeManager;
    Tetromino tetromino;
    //controls
    int dx = 0, dy = 0;
    bool is_rotate_clicked = false;
public:
    Game();
    void run();
    void readInput();
    void update();
    void draw();
};


#endif //TETRIS2_0_GAME_H
