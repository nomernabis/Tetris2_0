//
// Created by pavel on 11.02.18.
//

#ifndef TETRIS2_0_TETROMINO_H
#define TETRIS2_0_TETROMINO_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Constants.h"

struct Position{
    u_short x = 0, y = 0;
};

struct Rect{
    u_short left = 0, top = 0;
    u_short w = 0, h = 0;
    Rect() = default;
};

enum Type {I, L};
extern const u_short i_shape[N][N];
extern const u_short l_shape[N][N];

class Tetromino {
    Position p;
    Type t = Type::I;
    Rect rect;
    Rect calc_rect();
public:
    Tetromino() = default;
    void draw(u_short map[H][W]);
    void move(int dx, int dy);
    void clear(u_short map[H][W]);
};


#endif //TETRIS2_0_TETROMINO_H
