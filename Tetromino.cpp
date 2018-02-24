//
// Created by pavel on 11.02.18.
//
#include "Tetromino.h"
#include <iostream>

Tetromino::Tetromino(ShapeManager* s) : shapeManager{s} {
    std::srand(std::time(nullptr));
}

bool Tetromino::isInBounds(int x, int y) {
    return x >= 0 && x < W && y >= 0 && y < H;
}

void Tetromino::move(int dx, int dy, int map[H][W]) {

    Shape temp = shape;

    temp.position.x += dx;
    temp.position.y += dy;

    if (isInBounds(temp.right(), temp.down()) && isInBounds(temp.position.x, temp.position.y)) {
        //check for collisions
        if (!intersects(temp, map)) {
            shape = temp;
        } else {
            if (dy == 1) {
                fix(map);
            }
        }
    } else {
        //move down
        if (dy == 1) {
            fix(map);
        }
    }
}

bool Tetromino::intersects(Shape s, int map[H][W]) {
    for (int i = s.position.y; i <= s.down(); ++i) {
        for (int j = s.position.x; j <= s.right(); ++j) {
            if (s.body[i - s.position.y + s.rect.top][j - s.position.x + s.rect.left] == 1 && map[i][j] == 2) {
                return true;
            }
        }
    }
    return false;
}

void Tetromino::draw(int map[H][W]) {
    for (int i = shape.position.y; i <= shape.down(); ++i) {
        for (int j = shape.position.x; j <= shape.right(); ++j) {
            if (shape.body[i - shape.position.y + shape.rect.top][j - shape.position.x + shape.rect.left] == 1) {
                map[i][j] = shape.body[i - shape.position.y + shape.rect.top][j - shape.position.x + shape.rect.left];
            }
        }
    }
}

void Tetromino::clear(int map[H][W]) {

    for (int i = shape.position.y; i <= shape.down(); ++i) {
        for (int j = shape.position.x; j <= shape.right(); ++j) {
            if (map[i][j] == 1) {
                map[i][j] = 0;
            }
        }
    }
}

void Tetromino::fix(int map[H][W]) {
    for (int i = shape.position.y; i <= shape.down(); ++i) {
        for (int j = shape.position.x; j <= shape.right(); ++j) {
            if (shape.body[i - shape.position.y + shape.rect.top][j - shape.position.x + shape.rect.left] == 1) {
                map[i][j] = 2;
            }
        }
    }
    shape.position.x = 0;
    shape.position.y = 0;

    set_type(next_type);
    next_type = (Type) (std::rand() % 5);
}

/*
 * 1)Try rotate
 * 2)Detect part intersected
 * */

void Tetromino::move(int dx, int dy, Shape& temp, int map[H][W]){

    temp.position.x += dx;
    temp.position.y += dy;

    if (isInBounds(temp.right(), temp.down()) && isInBounds(temp.position.x, temp.position.y)) {
        //check for collisions
        if (!intersects(temp, map)) {
            shape = temp;
        } else {
            if (dy == 1) {
                fix(map);
            }
        }
    } else {
        //move down
        if (dy == 1) {
            fix(map);
        }
    }
}

void Tetromino::check_rotation_collisions(Shape &temp, int map[H][W]) {
    for (int i = temp.position.y; i <= temp.down(); ++i) {
        for (int j = temp.position.x; j <= temp.right(); ++j) {
            if (map[i][j] == 2 && temp.body[temp.top(i)][temp.left(j)] == 1) {
                //move left
                if (isInBounds(j - 1, i) && map[i][j - 1] == 0 &&
                    temp.body[temp.top(i)][temp.left(j) - 1] == 1) {
                    int dx = (j - 1) - temp.right();
                    move(dx, 0, temp, map);
                    return;
                }

                if (isInBounds(j, i - 1) && map[i - 1][j] == 0 && temp.body[temp.top(i) - 1][temp.left(j)] == 1) {
                    int dy = (i - 1) - temp.down();
                    move(0, dy, temp, map);
                    return;
                }

            }
        }
    }
}

void Tetromino::rotate(int map[H][W]) {
    Shape temp = shape;
    temp.rotate();

    if (isInBounds(temp.right(), temp.down())) {
        if (!intersects(temp, map)) {
            shape = temp;
        } else {
            check_rotation_collisions(temp, map);
        }
    } else {
        if (intersects(temp, map)) {
            check_rotation_collisions(temp, map);
        } else {
            int dx = 0, dy = 0;
            if (temp.right() > W - 1) {
                dx = (W - 1) - temp.right();
            }
            if (temp.down() > H - 1) {
                dy = (H - 1) - temp.down();
            }
            move(dx, dy, temp, map);
        }

    }

}

void Tetromino::set_type(Type t) {
    type = t;
    shape = shapeManager->get(t);
}

Type Tetromino::get_next_type() {
    return next_type;
}

void Tetromino::set_shape_manager(ShapeManager *sm) {
    shapeManager = sm;
    set_type((Type) (std::rand() % 5));
    next_type = (Type) (std::rand() % 5);
}