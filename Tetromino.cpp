//
// Created by pavel on 11.02.18.
//
#include "Tetromino.h"
#include <iostream>

Tetromino::Tetromino(ShapeManager &s) : shapeManager{s} {
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

    //std::cout << "shit " << std::rand() % 5 << "\n";
    //set_type((Type)(std::rand() % 5));
}

/*
 * 1)Try rotate
 * 2)Detect part intersected
 * */
void Tetromino::rotate(int map[H][W]) {

    Shape temp = shape;
    temp.rotate();


    if (isInBounds(temp.right(), temp.down())) {
        if (!intersects(temp, map)) {
            std::cout << "ok\n";
            shape = temp;
        } else {
            std::cout << "not ok\n";
            for (int i = temp.position.y; i <= temp.down(); ++i) {
                for (int j = temp.position.x; j <= temp.right(); ++j) {
                    if (map[i][j] == 2 &&
                        temp.body[i - temp.position.y + temp.rect.top][j - temp.position.x + temp.rect.left] == 1) {
                        //move left
                        if (isInBounds(j - 1, i) && map[i][j - 1] == 0 &&
                            temp.body[i - temp.position.y + temp.rect.top][j - temp.position.x + temp.rect.left - 1] == 1) {
                            int dx = (j - 1) - temp.right();
                            shape = temp;
                            move(dx, 0, map);
                            std::cout << "not ok1\n";
                            return;
                        }

                        if (isInBounds(j, i - 1) && map[i - 1][j] == 0 &&
                            temp.body[i - temp.position.y + temp.rect.top - 1][j - temp.position.x + temp.rect.left] ==
                            1) {
                            int dy = (i - 1) - temp.down();
                            shape = temp;
                            move(0, dy, map);
                            std::cout << "not ok2\n";
                            return;
                        }

                    }
                }
            }
        }
    } else {

        if (intersects(temp, map)) {
            for (int i = temp.position.y; i <= temp.down(); ++i) {
                for (int j = temp.position.x; j <= temp.right(); ++j) {
                    if (map[i][j] == 2 &&
                        temp.body[i - temp.position.y + temp.rect.top][j - temp.position.x + temp.rect.left] == 1) {
                        //move left
                        if (isInBounds(j - 1, i) && map[i][j - 1] == 0 &&
                            temp.body[i - temp.position.y + temp.rect.top][j - temp.position.x + temp.rect.left - 1] ==
                            1) {
                            int dx = (j - 1) - temp.right();
                            shape = temp;
                            move(dx, 0, map);
                            return;
                        }
                        if (isInBounds(j, i - 1) && map[i - 1][j] == 0 &&
                            temp.body[i - temp.position.y + temp.rect.top - 1][j - temp.position.x + temp.rect.left] ==
                            1) {
                            int dy = (i - 1) - temp.down();
                            shape = temp;
                            move(0, dy, map);
                            return;
                        }
                    }
                }
            }
        } else {
            int dx = 0, dy = 0;
            if (temp.right() > W - 1) {
                dx = (W - 1) - temp.right();
            }
            if (temp.down() > H - 1) {
                dy = (H - 1) - temp.down();
            }
            shape = temp;
            move(dx, dy, map);
            return;
        }

    }

}

void Tetromino::set_type(Type t) {
    type = t;
    shape = shapeManager.get(type);
}