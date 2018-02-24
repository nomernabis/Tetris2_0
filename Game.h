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
    bool need_to_remove = false;
    bool removed_rows[H] = { false };
    bool calc_rows();
    void remove_rows();
    void draw_next_shape();
    //
    int scores = 0;
    //
    sf::Font atarian_font;
    sf::Text text;
    sf::RectangleShape vertical_border;
public:
    Game();
    void run();
    void readInput();
    void update();
    void draw();
    Type next_type = Type::L;
};


#endif //TETRIS2_0_GAME_H
