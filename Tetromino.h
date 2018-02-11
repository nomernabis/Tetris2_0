//
// Created by pavel on 11.02.18.
//

#ifndef TETRIS2_0_TETROMINO_H
#define TETRIS2_0_TETROMINO_H

#include "Constants.h"

struct Position{
    u_short x = 0, y = 0;
};
enum Type {I, L};
extern const u_short i_shape[N][N];
extern const u_short l_shape[N][N];

class Tetromino {
    Position p;
    Type t = Type::I;
public:
    Tetromino() = default;
    void draw(u_short map[H][W]);
    void move(int dx, int dy);
};


#endif //TETRIS2_0_TETROMINO_H
