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

enum State{running, pause_state, fail};
class Game {
    State currentState;
    sf::RenderWindow m_renderWindow;
    sf::RectangleShape m_cell, m_pauseRect, m_filterRect;
    int map[H][W] = {};
    ShapeManager m_shapeManager;
    Tetromino tetromino;
    //controls
    int dx = 0, dy = 0;
    bool is_rotate_clicked = false;
    bool need_to_remove = false;
    bool removed_rows[H] = { false };
    //methods
    bool calc_rows();
    void remove_rows();
    void draw_next_shape();
    void play_animation();
    void processPause();
    void drawIndex();
    void processMenu();
    void clearMap();
    float calcCenteredX(sf::Text& text, sf::RectangleShape& rect) const;
    float marginTop(sf::Transformable& relativeTo, float margin) const;
    sf::Vector2f drawMenu(std::string title, sf::Transformable& relativeTo, sf::RectangleShape& parent, float marginTop);
    //
    static const int RESUME = 0;
    static const int RESTART = 1;
    static const int EXIT = 2;
    //
    void resume();
    void restart();
    void exit();
    //
    void processFail();
    //
    int scores = 0;
    //
    sf::Font atarian_font;
    sf::Text text;
    sf::RectangleShape vertical_border;
    //
    //menu vars
    sf::Vector2f coords[3];
    int current_index = 0;
    //
    float elapsed = 0;
    sf::Clock clock;
public:
    Game();
    void run();
    void readInput();
    void update();
    void draw();
};


#endif //TETRIS2_0_GAME_H
