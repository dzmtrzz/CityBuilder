#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include "Buildings.h"
#include "Data_types.h"

class Tile {
    private:
        std::unique_ptr<sf::RectangleShape> tile = std::make_unique<sf::RectangleShape>();
        sf::Vector2f pos;
        sf::Vector2f size;

        Building_Current state = Building_Current::None;
        std::unique_ptr<Building> building = nullptr;
    public:
        explicit Tile(sf::Vector2f pos, sf::Vector2f size);
        void update(std::array<Neighbor, 4> neighbor_tiles) {building->update(neighbor_tiles);};

        Building_Current getState() const {return state;};
        void setState(); // make sure to change `building` along with state

        const sf::Sprite& getBuildingSprite() const {return building->getSprite();};
        sf::RectangleShape& getTile() {return *tile;};
};