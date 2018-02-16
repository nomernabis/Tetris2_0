//
// Created by pavel on 15.02.18.
//

#ifndef TETRIS2_0_SHAPEMANAGER_H
#define TETRIS2_0_SHAPEMANAGER_H
#include <map>
#include "Shape.h"
#include "shapes.h"


class ShapeManager {
    std::map<Type, Shape> m_shape_map;
public:
    Shape get(Type t);
    void add(Type t, Shape s);
};


#endif //TETRIS2_0_SHAPEMANAGER_H
