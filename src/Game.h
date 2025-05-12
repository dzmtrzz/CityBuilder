#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>
#include "Data_types.h"
#include "Tile.h"

class Game {
    private:
        sf::Vector2f GameRes;
        std::string GameTitle;

        const int tilesPerRow;
        std::vector<std::unique_ptr<Tile>> tileGrid;

        Building_Current selectedBuildingType = Building_Current::None;

        void render();
        void inputHandler();

        void init_world(sf::Vector2f size);
    public:
        explicit Game(int n) : tilesPerRow(n) {};
        int run();
};