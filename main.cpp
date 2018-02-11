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

int main() {
    u_short map[H][W] = {};
    Tetromino t;


    sf::RenderWindow window(sf::VideoMode(250, 500), "Tetris");
    window.setFramerateLimit(60);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(event.key.code == sf::Keyboard::Down){
                t.move(0, 1);
            }
        }
        window.clear(sf::Color::White);
        window.display();
        t.draw(map);
        print(map);
    }
    return 0;
}