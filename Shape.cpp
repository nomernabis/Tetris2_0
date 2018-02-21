//
// Created by pavel on 15.02.18.
//
#include "Shape.h"


Shape::Shape(const int body[N][N]) {
    for(size_t i=0; i < N; ++i){
        for(size_t j=0; j < N; ++j){
            this->body[i][j] = body[i][j];
        }
    }
    rect = calc_rect();
}

Shape::Shape(const Shape& rhs){
    for(size_t i=0; i < N; ++i){
        for(size_t j=0; j < N; ++j){
            body[i][j] = rhs.body[i][j];
        }
    }
    rect = rhs.rect;
    position = rhs.position;
}

void Shape::rotate() {
    int temp[N][N] = {};
    for(size_t i=0; i < N; ++i){
        for(size_t j=0; j < N; ++j){
            temp[i][j] = body[j][i];
        }
    }

    for(size_t i=0; i < N; ++i){
        for(size_t j=0; j < N; ++j){
            body[i][j] = temp[i][j];
        }
    }

    rect = calc_rect();
}

Rect Shape::calc_rect() {
    int left = 4, top = 4;
    int right = 0, down = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (body[i][j] == 1) {
                if (i < top) {
                    top = i;
                }
                if (j < left) {
                    left = j;
                }
                if (i > down) {
                    down = i;
                }
                if (j > right) {
                    right = j;
                }
            }
        }
    }

    Rect rect;
    rect.left = left;
    rect.top = top;
    rect.w = right - left + 1;
    rect.h = down - top + 1;
    return rect;
}

int Shape::right() {
    return position.x + rect.w - 1;
}

int Shape::down() {
    return position.y + rect.h - 1;
}

int Shape::left(int j){
    return j - position.x + rect.left ;
}

int Shape::top(int i) {
    return i - position.y + rect.top;
}