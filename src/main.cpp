
#include "Data_types.h"
#include "Game.h"
#include "Tile.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <array>
#include <iostream>
#include <ostream>
#include <vector>

Tile::Tile(sf::Vector2f pos, sf::Vector2f size) : pos(pos), size(size) {
    tile->setSize(size);
    tile->setPosition(pos);
    tile->setFillColor(sf::Color::Green);
    tile->setOutlineColor(sf::Color::Black);

};

void Game::inputHandler() {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == event.MouseButtonPressed)
            switch (event.mouseButton.button) {
                case (sf::Mouse::Left):
                    {
                    int idx = 0;
                    for (const auto& tile : tileGrid) {
                        if (tile->getTile().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            std::array<Neighbor, 4> a = get_neighbors(tileGrid.begin() + idx);
                            std::cout << static_cast<int>(a[0].direction) << static_cast<int>(a[1].direction) << static_cast<int>(a[2].direction) << static_cast<int>(a[3].direction) << std::endl;
                        }
                        idx += 1;
                    }
                    }
                    break;
                default:
                    break;
            }
        } 
    }


void Game::render() {
    window.clear();
    
    for (const auto& tile : tileGrid) {
        window.draw(tile->getTile());
    }

    window.display();
}

void Game::logic() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    for (const auto& tile : tileGrid) {
        if (tile->getTile().getGlobalBounds().contains(mousePos)) {
            tile->getTile().setOutlineThickness(-10);
        } else tile->getTile().setOutlineThickness(0);
    }
}

int Game::run() {
    init_world(sf::Vector2f(GameRes.width, GameRes.height));

    while (window.isOpen())
    {
        inputHandler();
        logic();

        render();
    }
    return 0;
}

int main() {
    Game game(sf::VideoMode(640, 640), "CityBuilder", 10);

    game.run();
    return 0;
}