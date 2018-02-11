//
// Created by pavel on 11.02.18.
//
#include <iostream>
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
    rect = calc_rect();

    Position temp = p;
    temp.x += dx;
    temp.y += dy;

    std::cout << rect.w << "\n";
    if(temp.x >= 0 && temp.x + rect.w - 1 < W && temp.y >= 0 && temp.y + rect.h - 1 < H){
        p = temp;
    }
}

void Tetromino::draw(u_short map[H][W]) {
    rect = calc_rect();
    for(size_t i=0; i < N; ++i){
        for(size_t j=0; j < N; ++j){
            if(i_shape[i][j] == 1){
                map[i - rect.top + p.y][j - rect.left + p.x] = i_shape[i][j];
            }
        }
    }
}

void Tetromino::clear(u_short map[H][W]) {
    for(size_t i = p.y; i < p.y + N; ++i){
        for(size_t j= p.x; j < p.x + N; ++j){
            if(map[i][j] == 1){
                map[i][j] = 0;
            }
        }
    }
}

Rect Tetromino::calc_rect(){
    u_short left = 4, top = 4;
    u_short right = 0, down = 0;
    for(u_short i=0; i < N; ++i){
        for(u_short j=0; j < N; ++j){
            if(i_shape[i][j] == 1){
                if(i < top){
                    top = i;
                }
                if(j < left){
                    left = j;
                }
                if(i > down){
                    down = i;
                }
                if(j > right){
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