#include <iostream>
#include "Constants.h"
#include "Tetromino.h"
#include "ShapeManager.h"
#include "shapes.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


void print(u_short map[H][W]){
    for(size_t i=0; i < H; ++i){
        for(size_t j=0; j < W; ++j){
            std::cout << map[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void draw(u_short map[H][W], sf::RenderWindow& window){
    sf::RectangleShape cell;
    cell.setSize({25, 25});
    cell.setFillColor(sf::Color::Black);

    for(int i=0; i < H; ++i){
        for(int j=0; j < W; ++j){
            if(map[i][j] != 0){
                cell.setPosition(25*j, 25*i);
                window.draw(cell);
            }
        }
    }
}




int main() {

    ShapeManager shape_manager;

    Shape m_i_shape(i_shape);
    Shape m_l_shape(l_shape);
    Shape m_z_shape(z_shape);
    Shape m_t_shape(t_shape);
    Shape m_o_shape(o_shape);

    shape_manager.add(Type::I, m_i_shape);
    shape_manager.add(Type::L, m_l_shape);
    shape_manager.add(Type::Z, m_z_shape);
    shape_manager.add(Type::T, m_t_shape);
    shape_manager.add(Type::O, m_o_shape);

    u_short map[H][W] = {};
    Tetromino t(shape_manager);

    sf::RenderWindow window(sf::VideoMode(250, 500), "Tetris");
    window.setFramerateLimit(60);

    while (window.isOpen()){
        sf::Event event;

        t.clear(map);
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                t.move(0, 1, map);
                print(map);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                t.move(-1, 0, map);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                t.move(1, 0, map);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                t.rotate(map);
            }
        }
        window.clear(sf::Color::White);
        t.draw(map);
        draw(map, window);
        window.display();
    }
    return 0;
}