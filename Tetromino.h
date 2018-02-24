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
    Type type;
    Type next_type;
    Shape shape;
    ShapeManager* shapeManager = nullptr;
    void fix(int map[H][W]);
    bool intersects(Shape shape, int map[H][W]);
    bool isInBounds(int x, int y);
    void move(int dx, int dy, Shape& shape, int map[H][W]);
    void check_rotation_collisions(Shape& temp, int map[H][W]);
public:
    Tetromino() = default;
    explicit Tetromino(ShapeManager* sm);
    void draw(int map[H][W]);
    void move(int dx, int dy, int map[H][W]);
    void clear(int map[H][W]);
    void rotate(int map[H][W]);
    void set_type(Type t);
    void set_shape_manager(ShapeManager* sm);
    Type get_next_type();
};


#endif //TETRIS2_0_TETROMINO_H
