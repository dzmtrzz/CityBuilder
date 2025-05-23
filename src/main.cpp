
#include "Data_types.h"
#include "Game.h"
#include "Tile.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <array>
#include <format>
#include <utility>
#include <vector>

void Game::inputHandler() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::Resized) {
            // resize my view
            view.setSize({
                    static_cast<float>(event.size.width),
                    static_cast<float>(event.size.height)
            });
            window.setView(view);
        }
        if (event.type == event.MouseButtonPressed)
            switch (event.mouseButton.button) {
                case (sf::Mouse::Left):
                    {
                    for (const auto& button : buttons) {
                        if (button->get_shape().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            button->click(*this);
                            return; // if we click a button, we don't want to click a tile, do we?
                        }
                    }


                    int idx = 0;
                    for (const auto& tile : world.getTileGrid()) {
                        if (tile->getTile().getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                            std::array<Neighbor, 4> a = world.get_neighbors(world.getTileGrid().begin() + idx);


                            if (selectedBuildingType != tile->getState()) {
                                if (money + BuildCost[tile->getState()]/2 >= BuildCost[selectedBuildingType]) {
                                    money += BuildCost[tile->getState()]/2;
                                    if (tile->getState() != Building_Current::None) tile->setTileEffect();
                                    tile->setState(selectedBuildingType);
                                    money -= BuildCost[selectedBuildingType];

                                    tile->updateBuilding(a);
                                }
                            }

                            for (const auto& neighbor : a) {
                                if (neighbor.tile != nullptr) {
                                    neighbor.tile->updateBuilding(world.get_neighbors(neighbor.it));
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
        }
        if (event.type == sf::Event::MouseWheelScrolled) {
            world.scale(1.f + event.mouseWheelScroll.delta/20);
        }
    }
}

void Game::render() {
    window.clear();

    for (const auto& tile : world.getTileGrid()) {
        window.draw(tile->getTile());
        if (tile->getState() != Building_Current::None)
            window.draw(tile->getBuildingSprite(), tile->getTile().getTransform());
        if (tile->getTileEffect() != nullptr)
            window.draw(tile->getTileEffect()->get_drawable(), tile->getTile().getTransform());
    }

    for (const auto& button : buttons) {
        window.draw(button->get_drawable());
    }

    window.draw(text_elements[0]->get_drawable());

    window.display();
}

void Game::uiLogic() {
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

    text_elements[0]->setSecondaryText(std::format("{}", money));
    text_elements[0]->update();

    int position = 0;
    for (const auto& elem : buttons) {
        elem->setPosition(window.mapPixelToCoords(sf::Vector2i(position, view.getSize().y - 30)));
        position += 30;
    }

    text_elements[0]->setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
}


void Game::logic() {
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        mousePos = sf::Mouse::getPosition(window);
    }
    else {
        mousePos2 = sf::Mouse::getPosition(window);
        offset += -(window.mapPixelToCoords(mousePos2) - window.mapPixelToCoords(mousePos));
        mousePos = sf::Mouse::getPosition(window);
        view.setCenter(offset);
    }


    if (logicClock.getElapsedTime().asSeconds() >= 3)
        logicTime = logicClock.restart();
    for (const auto& tile : world.getTileGrid()) {
        if (tile->getTile().getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
            tile->getTile().setOutlineThickness(-5);
        } else tile->getTile().setOutlineThickness(0);

        if (tile->getState() == Building_Current::House) { //at some point this will have to be remade, but right now we only have one type of building that would generate money
            money += 10 * (logicTime.asSeconds()/3);
        }

        tile->updateEffect();
    }

    window.setView(view);

    logicTime = sf::Time::Zero;
}

int Game::run() {
    Tile::init_texture("assets/grass.png");

    window.setFramerateLimit(120);

    world.init_world(sf::Vector2f(GameRes.width, GameRes.height));

    buttons.push_back(std::make_unique<Button>(sf::Vector2f(0, GameRes.height-30), sf::Vector2f(30, 30), std::function<void(Game&)>([](Game& game) {game.setCurrentBuildingType(Building_Current::None);})));
    buttons[0]->init_texture("assets/expl.png", sf::IntRect(0, 0, 100, 100));

    buttons.push_back(std::make_unique<Button>(sf::Vector2f(30, GameRes.height-30), sf::Vector2f(30, 30), std::function<void(Game&)>([](Game& game) {game.setCurrentBuildingType(Building_Current::House);})));
    buttons[1]->init_texture("assets/house.png", sf::IntRect(0, 0, 100, 100));

    buttons.push_back(std::make_unique<Button>(sf::Vector2f(30*2, GameRes.height-30), sf::Vector2f(30, 30), std::function<void(Game&)>([](Game& game) {game.setCurrentBuildingType(Building_Current::Road);})));
    buttons[2]->init_texture("assets/road-s.png", sf::IntRect(0, 0, 100, 100));

    House::init_texture("assets/house.png");

    TextElement::load_font("assets/Roboto-Regular.ttf");

    text_elements.push_back(std::make_unique<TextElement>("Money amount:", std::format("{}", money), sf::Vector2f(0,0)));

    Explosion::init_texture("assets/expl.png");

    while (window.isOpen())
    {
        inputHandler();

        logic();
        uiLogic();

        render();

    }
    return 0;
}

int main() {
    Game game(sf::VideoMode(1280, 720), "CityBuilder", 40, 30);

    game.run();
    return 0;
}