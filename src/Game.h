#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>
#include <string>
#include <vector>
#include "Data_types.h"
#include "Tile.h"

class Game {
    private:
        sf::VideoMode GameRes;
        std::string GameTitle;
        sf::RenderWindow window = sf::RenderWindow(GameRes, GameTitle);

        // world-related (might split into separate class)
        const int tilesPerRow;
        std::vector<std::unique_ptr<Tile>> tileGrid;
        void init_world(sf::Vector2f size);
        std::array<Neighbor, 4> get_neighbors(std::vector<std::unique_ptr<Tile>>::const_iterator iter);

        Building_Current selectedBuildingType = Building_Current::None;

        void render();
        void inputHandler();
        void logic();


    public:
        explicit Game(sf::VideoMode resolution, std::string title, int n) : GameRes(resolution), GameTitle(title), tilesPerRow(n) {};
        int run();
};