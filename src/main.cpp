
#include "Data_types.h"
#include "Game.h"
#include "Tile.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <array>
#include <utility>
#include <vector>


Button::Button(sf::Vector2f buttonPos, sf::Vector2f buttonDim, std::function<void(Game&)> onClick) : on_click(std::move(onClick)) {
    button->setPosition(buttonPos);
    button->setSize(buttonDim);
    button->setFillColor(sf::Color(173, 171, 163,255)); // gray
    button->setOutlineColor(sf::Color::Black);
}

void Button::init_texture(const std::string &path, sf::IntRect dimensions) {
    if (!texture.loadFromFile(path, dimensions)) {
        throw std::runtime_error("Failed to load texture");
    }

    button->setTexture(&texture);
}

void Button::update(bool is_selected) {
    if (is_selected) {
        button->setOutlineThickness(-2);
    } else {
        button->setOutlineThickness(0);
    }
}



void Game::inputHandler() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == event.MouseButtonPressed)
            switch (event.mouseButton.button) {
                case (sf::Mouse::Left):
                    {
                    for (const auto& button : buttons) {
                        if (button->get_shape().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            button->click(*this);
                            uilogic();
                            return; // if we click a button, we don't want to click a tile, do we?
                        }
                    }


                    int idx = 0;
                    for (const auto& tile : world.getTileGrid()) {
                        if (tile->getTile().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            std::array<Neighbor, 4> a = world.get_neighbors(world.getTileGrid().begin() + idx);
                            tile->setState(selectedBuildingType);
                            tile->update(a);

                            for (const auto& neighbor : a) {
                                if (neighbor.tile != nullptr) {
                                    neighbor.tile->update(world.get_neighbors(neighbor.it));
                                }
                            }
                        }
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
            uilogic();
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

    for (const auto& button : buttons) {
        window.draw(button->get_drawable());
    }

    window.display();
}

void Game::uilogic() {
    if (selectedBuildingType == Building_Current::None) {
        buttons[0]->update(true);
        buttons[1]->update(false);
        buttons[2]->update(false);
    } else if (selectedBuildingType == Building_Current::House) {
        buttons[0]->update(false);
        buttons[1]->update(true);
        buttons[2]->update(false);
    } else {
        buttons[0]->update(false);
        buttons[1]->update(false);
        buttons[2]->update(true);
    }
}


void Game::logic() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));


    for (const auto& tile : world.getTileGrid()) {
        if (tile->getTile().getGlobalBounds().contains(mousePos)) {
            tile->getTile().setOutlineThickness(-5);
        } else tile->getTile().setOutlineThickness(0);
    }

}

int Game::run() {
    Tile::init_texture("assets/grass.png");

    world.init_world(sf::Vector2f(GameRes.width, GameRes.height));

    buttons.push_back(std::make_unique<Button>(sf::Vector2f(0, GameRes.height-30), sf::Vector2f(30, 30), std::function<void(Game&)>([](Game& game) {game.setCurrentBuildingType(Building_Current::None);})));
    buttons[0]->init_texture("assets/expl.png", sf::IntRect(0, 0, 100, 100));

    buttons.push_back(std::make_unique<Button>(sf::Vector2f(30, GameRes.height-30), sf::Vector2f(30, 30), std::function<void(Game&)>([](Game& game) {game.setCurrentBuildingType(Building_Current::House);})));
    buttons[1]->init_texture("assets/house.png", sf::IntRect(0, 0, 100, 100));

    buttons.push_back(std::make_unique<Button>(sf::Vector2f(30*2, GameRes.height-30), sf::Vector2f(30, 30), std::function<void(Game&)>([](Game& game) {game.setCurrentBuildingType(Building_Current::Road);})));
    buttons[2]->init_texture("assets/road-s.png", sf::IntRect(0, 0, 100, 100));

    House::init_texture("assets/house.png");

    while (window.isOpen())
    {
        inputHandler();
        logic();

        render();
    }
    return 0;
}

int main() {
    Game game(sf::VideoMode(960, 960), "CityBuilder", 10);

    game.run();
    return 0;
}