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
        const int numRows;
        std::vector<std::unique_ptr<Tile>> tileGrid;
    public:
        explicit GameWorld(const int tilesPerRow, const int numRows) : tilesPerRow(tilesPerRow), numRows(numRows) {}
        void init_world(sf::Vector2f size);
        std::vector<std::unique_ptr<Tile>>& getTileGrid() {return tileGrid;}
        [[nodiscard]] std::array<Neighbor, 4> get_neighbors(std::vector<std::unique_ptr<Tile>>::const_iterator iter) const;
        void scale(float factor, sf::Vector2f mouseWorldPos);
};

class Game {
    private:
        sf::VideoMode GameRes;
        std::string GameTitle;
        sf::RenderWindow window = sf::RenderWindow(GameRes, GameTitle, sf::Style::Resize | sf::Style::Close);

        sf::View view;

        GameWorld world;
        std::vector<std::unique_ptr<Button>> buttons;
        std::vector<std::unique_ptr<TextElement>> text_elements;

        Building_Current selectedBuildingType = Building_Current::None;

        sf::Vector2i mousePos;
        sf::Vector2i mousePos2;
        sf::Vector2f offset = {0.f, 0.f};

        int money=500;
        std::map<Building_Current, int> BuildCost {
            {Building_Current::House, 50},
            {Building_Current::Road, 10},
            {Building_Current::None, 0}
        };

        sf::Transform globalTransform;

        void render();
        void inputHandler();

        sf::Clock logicClock;
        void logic();
        sf::Time logicTime;

        void uiLogic();
    public:
        explicit Game(sf::VideoMode resolution, std::string  title, int tilesPerRow, int numRows) : GameRes(resolution), GameTitle(std::move(title)), world(GameWorld(tilesPerRow, numRows)) {}
        void setCurrentBuildingType(Building_Current type) {selectedBuildingType = type;}
        int run();
};