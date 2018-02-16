//
// Created by pavel on 15.02.18.
//

#ifndef TETRIS2_0_SHAPE_H
#define TETRIS2_0_SHAPE_H

#include <zconf.h>
#include "Constants.h"


struct Position{
    int x = 0, y = 0;
};
struct Rect{
    int left = 0, top = 0;
    int w = 0, h = 0;
};

class Shape{
public:
    int body[N][N] = {0};
    Rect rect;
    Position position;

    void rotate();
    Rect calc_rect();

    Shape() = default;
    explicit Shape(const int body[N][N]);
    //copy constructor
    Shape(const Shape& rhs);
};
#endif //TETRIS2_0_SHAPE_H
