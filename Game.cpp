//
// Created by pavel on 16.02.18.
//

#include <iostream>
#include "Game.h"

Game::Game()
        :m_renderWindow(sf::VideoMode(W * CELL_SIZE + SCREEN_PADDING * 2, H * CELL_SIZE), "Tetris"){

    Shape m_i_shape(i_body),
            m_l_shape(l_body),
            m_z_shape(z_body),
            m_t_shape(t_body),
            m_o_shape(o_body);

    m_shapeManager.add(Type::I, m_i_shape);
    m_shapeManager.add(Type::L, m_l_shape);
    m_shapeManager.add(Type::Z, m_z_shape);
    m_shapeManager.add(Type::T, m_t_shape);
    m_shapeManager.add(Type::O, m_o_shape);

    m_renderWindow.setFramerateLimit(60);

    m_cell.setSize({25, 25});
    m_cell.setFillColor(sf::Color::Black);


    //load font
    if(!atarian_font.loadFromFile("assets/fonts/atarian.ttf")){

    }
    text.setFont(atarian_font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    //
    vertical_border.setFillColor(sf::Color::Black);
    vertical_border.setSize({BORDER_WIDTH, H * CELL_SIZE});
    //
    sf::Color blackFilter = sf::Color::Black;
    blackFilter.a = 128;

    m_filterRect.setFillColor(blackFilter);
    m_filterRect.setSize({m_renderWindow.getSize().x, m_renderWindow.getSize().y});

    const int p_box_width = 200;
    const int p_box_height = 250;

    m_pauseRect.setFillColor(sf::Color::White);
    m_pauseRect.setSize({p_box_width, p_box_height});
    m_pauseRect.setPosition((W * CELL_SIZE + 2 * SCREEN_PADDING)/ 2 - p_box_width / 2,
                            H * CELL_SIZE / 2 - p_box_height / 2);



    tetromino.set_shape_manager(&m_shapeManager);
}

void Game::processPause() {
    sf::Event event;
    while (m_renderWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            m_renderWindow.close();
        }
        if(event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::P:
                    is_running = !is_running;
                    break;
                default:
                    break;
            }
        }
    }

}

void Game::run() {
    while(m_renderWindow.isOpen()){
        if(is_running){
            readInput();
            update();
        } else {
            processPause();
        }
        draw();
    }
}

void Game::readInput() {
    sf::Event event;
    while (m_renderWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            m_renderWindow.close();
        }
        if(event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::Left:
                    dx = -1;
                    break;
                case sf::Keyboard::Right:
                    dx = 1;
                    break;
                case sf::Keyboard::Down:
                    dy = 1;
                    break;
                case sf::Keyboard::Up:
                    is_rotate_clicked = true;
                    break;
                case sf::Keyboard::P:
                    is_running = !is_running;
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::update() {
    tetromino.clear(map);
    if(dx || dy){
        tetromino.move(dx, dy, map);
    }
    if(is_rotate_clicked){
        tetromino.rotate(map);
    }
    tetromino.draw(map);

    need_to_remove = calc_rows();
    if(need_to_remove){
        //DRAWING IN UPDATE
        play_animation();
        remove_rows();
    }
    need_to_remove = false;

    dx = 0, dy = 0;
    is_rotate_clicked = false;
}

void Game::draw_next_shape() {
    int mini_size = CELL_SIZE;
    m_cell.setSize({mini_size, mini_size});

    Shape next_shape = m_shapeManager.get(tetromino.get_next_type());

    int width = next_shape.rect.w * CELL_SIZE;

    text.setString("Next");
    text.setPosition(SCREEN_PADDING / 2 - text.getLocalBounds().width / 2, 50);
    m_renderWindow.draw(text);

    for(int i=next_shape.rect.top; i < next_shape.rect.top + next_shape.rect.h; ++i){
        for(int j = next_shape.rect.left; j <= next_shape.rect.left + next_shape.rect.w; ++j){
            if(next_shape.body[i][j] == 1){
                m_cell.setPosition( (SCREEN_PADDING - width)/2 + j*mini_size, 100 + i*mini_size);
                m_renderWindow.draw(m_cell);
            }
        }
    }
    m_cell.setSize({CELL_SIZE, CELL_SIZE});
}

void Game::draw() {
    m_renderWindow.clear(sf::Color::White);

    //draw border
    vertical_border.setPosition(SCREEN_PADDING, 0);
    m_renderWindow.draw(vertical_border);
    vertical_border.setPosition(W * CELL_SIZE + SCREEN_PADDING, 0);
    m_renderWindow.draw(vertical_border);
    //draw lines
    text.setString("Lines");
    text.setPosition(W * CELL_SIZE + SCREEN_PADDING + SCREEN_PADDING / 2 - text.getLocalBounds().width / 2, 50);
    m_renderWindow.draw(text);
    text.setString(std::to_string(scores));
    text.setPosition(W * CELL_SIZE + SCREEN_PADDING + SCREEN_PADDING / 2 - text.getLocalBounds().width / 2, 90);
    m_renderWindow.draw(text);

    draw_next_shape();

    for(int i=0; i < H; ++i){
        for(int j=0; j < W; ++j){
            if(map[i][j] != 0){
                m_cell.setPosition(SCREEN_PADDING + CELL_SIZE * j, CELL_SIZE * i);
                m_renderWindow.draw(m_cell);
            }
        }
    }

    if(!is_running){
        m_renderWindow.draw(m_filterRect);
        m_renderWindow.draw(m_pauseRect);

        drawMenu("Menu", m_pauseRect, m_pauseRect, 20);
        drawMenu("Resume", text, m_pauseRect, 40);
        drawMenu("Restart", text, m_pauseRect, 40);
        drawMenu("Exit", text, m_pauseRect, 40);
    }
    m_renderWindow.display();
}

void Game::drawMenu(std::string title, sf::Transformable& relativeTo, sf::RectangleShape& parent, float margin){
    text.setString(title);
    text.setPosition(calcCenteredX(text, parent), marginTop(relativeTo, margin));
    m_renderWindow.draw(text);
}

float Game::marginTop(sf::Transformable& relativeTo, float margin) const {
    return relativeTo.getPosition().y + margin;
}

float Game::calcCenteredX(sf::Text& text, sf::RectangleShape& rect) const {
    return rect.getPosition().x + rect.getSize().x / 2 - text.getLocalBounds().width / 2;
}

bool Game::calc_rows() {

    for(int i=0; i < H; ++i){
        removed_rows[i] = false;
    }

    for(int i=0; i < H; ++i){
        bool is_full = true;
        for(int j=0; j < W; ++j){
            if(map[i][j] != 2){
                is_full = false;
                break;
            }
        }
        if(is_full){
            ++scores;
        }
        removed_rows[i] = is_full;
    }


    for(int i=0; i < H; ++i){
        if(removed_rows[i]) {
            return true;
        }
    }
    return false;
}

void Game::remove_rows() {
    int temp[H][W];
    tetromino.clear(map);

    for(int i=0; i < H; ++i){
        for(int j=0; j < W; ++j){
            temp[i][j] = map[i][j];
        }
    }

    int offset = 0;
    for(int i=H-1; i >= 0; --i){
        if(removed_rows[i]){
            offset++;
            continue;
        }

        for(int j=0; j < W; ++j){
            map[i + offset][j] = temp[i][j];
        }
    }

}

void Game::play_animation() {
    m_cell.setFillColor(sf::Color::Red);
    m_cell.setSize({CELL_SIZE, CELL_SIZE});
    for(int i=0; i < H; ++i){
        if(removed_rows[i]){
            for(int j=0; j < W; ++j){
                m_cell.setPosition(j * CELL_SIZE + SCREEN_PADDING, i * CELL_SIZE);
                m_renderWindow.draw(m_cell);
            }
        }
    }
    m_renderWindow.display();
    sf::sleep(sf::milliseconds(500));
    m_cell.setFillColor(sf::Color::Black);
}