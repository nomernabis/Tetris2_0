//
// Created by pavel on 11.02.18.
//

#ifndef TETRIS2_0_TETROMINO_H
#define TETRIS2_0_TETROMINO_H


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Shape.h"
#include "ShapeManager.h"

class Tetromino {
    Type t = Type::I;
    Shape shape;
    ShapeManager& shapeManager;
    void fix(u_short map[H][W]);
    bool intersects(Position pos, u_short shape[N][N], u_short map[H][W]);
public:
    explicit Tetromino(ShapeManager& sm);
    void draw(u_short map[H][W]);
    void move(int dx, int dy, u_short map[H][W]);
    void clear(u_short map[H][W]);
    void rotate(u_short map[H][W]);
};


#endif //TETRIS2_0_TETROMINO_H
