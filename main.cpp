#include <iostream>
#include "Constants.h"
#include "Tetromino.h"
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
            if(map[i][j] == 1){
                cell.setPosition(25*j, 25*i);
                window.draw(cell);
            }
        }
    }
}

int main() {
    u_short map[H][W] = {};
    Tetromino t;

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
                t.move(0, 1);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                t.move(-1, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                t.move(1, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){

            }
        }
        window.clear(sf::Color::White);
        t.draw(map);
        draw(map, window);
        window.display();
    }
    return 0;
}