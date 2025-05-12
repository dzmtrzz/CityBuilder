#include <SFML/Graphics.hpp>
#include "Data_types.h"
#include <array>
#include <memory>

class Building {
    private:
        std::unique_ptr<sf::Sprite> sprite;
    public:
        virtual void update(std::array<Neighbor, 4>) = 0;
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
