#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Data_types.h"
#include "Tile.h"
#include "UIElements.h"

class GameWorld {
    private:
        const int tilesPerRow;
        std::vector<std::unique_ptr<Tile>> tileGrid;
    public:
        explicit GameWorld(int n) : tilesPerRow(n) {}
        void init_world(sf::Vector2f size);
        std::vector<std::unique_ptr<Tile>>& getTileGrid() {return tileGrid;}
        [[nodiscard]] std::array<Neighbor, 4> get_neighbors(std::vector<std::unique_ptr<Tile>>::const_iterator iter) const;
};

class Game {
    private:
        sf::VideoMode GameRes;
        std::string GameTitle;
        sf::RenderWindow window = sf::RenderWindow(GameRes, GameTitle);

        GameWorld world;
        std::vector<std::unique_ptr<Button>> buttons;

        Building_Current selectedBuildingType = Building_Current::None;

        void render();
        void inputHandler();
        void logic();

        //TODO: come up with a better name :P
        void uilogic();
    public:
        explicit Game(sf::VideoMode resolution, std::string  title, int n) : GameRes(resolution), GameTitle(std::move(title)), world(GameWorld(n)) {}
        void setCurrentBuildingType(Building_Current type) {selectedBuildingType = type;}
        int run();
};