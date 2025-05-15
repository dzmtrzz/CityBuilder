
#include "Data_types.h"
#include "Game.h"
#include "Tile.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <array>
#include <vector>


void Game::inputHandler() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == event.MouseButtonPressed)
            switch (event.mouseButton.button) {
                case (sf::Mouse::Left):
                    {
                    int idx = 0;
                    for (const auto& tile : world.getTileGrid()) {
                        std::array<Neighbor, 4> a = world.get_neighbors(world.getTileGrid().begin() + idx);
                        if (tile->getTile().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            tile->setState(selectedBuildingType);
                        }
                        tile->update(a);
                        idx += 1;
                    }
                    }
                    break;
                default:
                    break;
            }
        if (event.type == event.KeyPressed) {
            switch (event.key.code) {
                case (sf::Keyboard::Key::Q) :
                    selectedBuildingType = Building_Current::None;
                    break;
                case (sf::Keyboard::Key::W) :
                    selectedBuildingType = Building_Current::House;
                    break;
                case (sf::Keyboard::Key::E) :
                    selectedBuildingType = Building_Current::Road;
                    break;
                default:
                    break;
            }
        }
    } 
}


void Game::render() {
    window.clear();
    
    for (const auto& tile : world.getTileGrid()) {
        window.draw(tile->getTile());
        if (tile->getState() == Building_Current::House)
            window.draw(tile->getBuildingSprite());
        if (tile->getState() == Building_Current::Road)
            window.draw(tile->getBuildingSprite()); 
    }

    window.display();
}

void Game::logic() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    
    int idx = 0;
    for (const auto& tile : world.getTileGrid()) {
        if (tile->getTile().getGlobalBounds().contains(mousePos)) {
            tile->getTile().setOutlineThickness(-5);
        } else tile->getTile().setOutlineThickness(0);

        std::array<Neighbor, 4> a = world.get_neighbors(world.getTileGrid().begin() + idx);
        tile->update(a);

        idx++;
    }
}

int Game::run() {
    world.init_world(sf::Vector2f(GameRes.width, GameRes.height));

    while (window.isOpen())
    {
        inputHandler();
        logic();

        render();
    }
    return 0;
}

int main() {
    Game game(sf::VideoMode(1440, 1440), "CityBuilder", 15);

    game.run();
    return 0;
}