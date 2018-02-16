//
// Created by pavel on 15.02.18.
//

#ifndef TETRIS2_0_SHAPE_H
#define TETRIS2_0_SHAPE_H

#include <zconf.h>
#include "Constants.h"


struct Position{
    u_short x = 0, y = 0;
};
struct Rect{
    u_short left = 0, top = 0;
    u_short w = 0, h = 0;
};

class Shape{
public:
    u_short body[N][N] = {0};
    Rect rect;
    Position position;

    void rotate();
    Rect calc_rect();

    Shape() = default;
    explicit Shape(const u_short body[N][N]);
    //copy constructor
    Shape(const Shape& rhs);
};
#endif //TETRIS2_0_SHAPE_H
