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

class GameWorld {
    private:
        const int tilesPerRow;
        std::vector<std::unique_ptr<Tile>> tileGrid;
    public:
        explicit GameWorld(int n) : tilesPerRow(n) {};
        void init_world(sf::Vector2f size);
        std::vector<std::unique_ptr<Tile>>& getTileGrid() {return tileGrid;};
        std::array<Neighbor, 4> get_neighbors(std::vector<std::unique_ptr<Tile>>::const_iterator iter) const;
};

class Game {
    private:
        sf::VideoMode GameRes;
        std::string GameTitle;
        sf::RenderWindow window = sf::RenderWindow(GameRes, GameTitle);

        GameWorld world;

        Building_Current selectedBuildingType = Building_Current::None;

        void render();
        void inputHandler();
        void logic();


    public:
        explicit Game(sf::VideoMode resolution, std::string title, int n) : GameRes(resolution), GameTitle(title), world(GameWorld(n)) {};
        int run();
};