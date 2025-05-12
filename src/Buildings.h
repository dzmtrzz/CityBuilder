#pragma once
#include <SFML/Graphics.hpp>
#include "Data_types.h"
#include <array>
#include <memory>

class Building {
    private:
        const std::unique_ptr<sf::Sprite> sprite;
        sf::Vector2f pos;
    public:
        virtual ~Building() = default;
        virtual void update(std::array<Neighbor, 4>) = 0;
        const sf::Sprite& getSprite() const {return *sprite;};
        void setPos();
};

class Road : public Building {
    public:
        void update(std::array<Neighbor, 4>);
};

class House : public Building {
    private:
        // add house type or smth like that
    public:
        void update(std::array<Neighbor, 4>);
};
