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
    rect.w = right - left + (int)1;
    rect.h = down - top + (int)1;
    return rect;
}
