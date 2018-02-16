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
    Type type = Type::I;
    Shape shape;
    ShapeManager& shapeManager;
    void fix(int map[H][W]);
    bool intersects(Position pos, int shape[N][N], int map[H][W]);
public:
    explicit Tetromino(ShapeManager& sm);
    void draw(int map[H][W]);
    void move(int dx, int dy, int map[H][W]);
    void clear(int map[H][W]);
    void rotate(int map[H][W]);
    void set_type(Type t);
};


#endif //TETRIS2_0_TETROMINO_H
