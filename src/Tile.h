#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include "Buildings.h"
#include "Data_types.h"

class Tile {
    private:
        sf::RectangleShape tile;
        sf::Vector2f pos;
        sf::Vector2f size;

        Building_Current state = Building_Current::None;
        std::unique_ptr<Building> building = nullptr;
    public:
        explicit Tile(sf::Vector2f pos, sf::Vector2f size) : pos(pos), size(size) {};
        void update(std::array<Neighbor, 4> neighbor_tiles) {building->update(neighbor_tiles);};

        Building_Current getState() const {return state;};
        void setState(); // make sure to change `building` along with state
        
        const sf::Sprite& getBuildingSprite() const {return building->getSprite();};
};