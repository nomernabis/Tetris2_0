//
// Created by pavel on 11.02.18.
//
#include <iostream>
#include "Tetromino.h"


Tetromino::Tetromino(ShapeManager& s): shapeManager{s} {

}

void Tetromino::move(int dx, int dy, int map[H][W]) {


    Position temp = shape.position;
    temp.x += dx;
    temp.y += dy;

    if (temp.x >= 0 && temp.x + shape.rect.w - 1 < W && temp.y >= 0 && temp.y + shape.rect.h - 1 < H) {
        //check for collisions
        if (!intersects(temp, shape.body, map)) {
            shape.position = temp;
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

bool Tetromino::intersects(Position pos, int shape[N][N], int map[H][W]) {
    for (int i = pos.y; i < pos.y + this->shape.rect.h; ++i) {
        for (int j = pos.x; j < pos.x + this->shape.rect.w; ++j) {
            if (shape[i - pos.y + this->shape.rect.top][j - pos.x + this->shape.rect.left] == 1 && map[i][j] == 2) {
                return true;
            }
        }
    }
    return false;
}

void Tetromino::draw(int map[H][W]) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (shape.body[i][j] == 1) {
                map[i - shape.rect.top + shape.position.y][j - shape.rect.left + shape.position.x] = shape.body[i][j];
            }
        }
    }
}

void Tetromino::clear(int map[H][W]) {

    for (size_t i = shape.position.y; i < shape.position.y + N; ++i) {
        for (size_t j = shape.position.x; j < shape.position.x + N; ++j) {
            if (map[i][j] == 1) {
                map[i][j] = 0;
            }
        }
    }
}

void Tetromino::fix(int map[H][W]) {
    for (int i = shape.position.y; i < shape.position.y + shape.rect.h; ++i) {
        for (int j = shape.position.x; j < shape.position.x + shape.rect.w; ++j) {
            if (shape.body[i - shape.position.y + shape.rect.top][j - shape.position.x + shape.rect.left] == 1) {
                map[i][j] = 2;
            }
        }
    }
    shape.position.x = 0;
    shape.position.y = 0;
}

/*
 * 1)Try rotate
 * 2)Detect part intersected
 * */
void Tetromino::rotate(int map[H][W]) {

    Shape temp = shape;
    temp.rotate();

    int lastX = temp.position.x + temp.rect.w - 1;
    int lastY = temp.position.y + temp.rect.h - 1;

    if(lastX < W && lastY < H){
        if(!intersects(temp.position, temp.body, map)){
            shape = temp;
        }
    } else {
        Position temp_pos;
        int dx = 0, dy = 0;
        if(lastX >= W){
            dx = (W - 1) - lastX;
        }
        if(lastY >= H){
            dy = (H - 1) - lastY;
        }
        temp_pos.x = temp.position.x + dx;
        temp_pos.y = temp.position.y + dy;

        if(!intersects(temp_pos, temp.body, map)){
            shape = temp;
            move(dx, dy, map);
        }
    }

}

void Tetromino::set_type(Type t) {
    type = t;
    shape = shapeManager.get(type);
}