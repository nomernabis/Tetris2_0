//
// Created by pavel on 15.02.18.
//
#include "Shape.h"


Shape::Shape(const u_short body[N][N]) {
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
    u_short temp[N][N] = {};
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
    u_short left = 4, top = 4;
    u_short right = 0, down = 0;
    for (u_short i = 0; i < N; ++i) {
        for (u_short j = 0; j < N; ++j) {
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
    rect.w = right - left + (u_short)1;
    rect.h = down - top + (u_short)1;
    return rect;
}
