//
// Created by pavel on 15.02.18.
//

#include "ShapeManager.h"

Shape ShapeManager::get(Type t) {
    auto it = m_shape_map.find(t);
    return it->second;
}

void ShapeManager::add(Type t, Shape s) {
    m_shape_map.insert(std::make_pair(t, s));
}