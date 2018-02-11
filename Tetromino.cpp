//
// Created by pavel on 11.02.18.
//
#include "Tetromino.h"

const u_short i_shape[N][N] = {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
};

const u_short l_shape[N][N] = {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
};


void Tetromino::move(int dx, int dy) {
    p.x += dx;
    p.y += dy;
}

void Tetromino::draw(u_short map[H][W]) {
    for(size_t i=0; i < N; ++i){
        for(size_t j=0; j < N; ++j){
            map[i + p.y][j + p.x] = i_shape[i][j];
        }
    }
}