#pragma once
#include <SFML/Graphics.hpp>
#include "Data_types.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <memory>

class Building {
    protected:
        const std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>();
        std::shared_ptr<sf::Texture> texture; //TODO: remove
        sf::Vector2f tilePos;
        sf::Vector2f tileSize;
    public:
        virtual ~Building() = default;
        virtual void update(std::array<Neighbor, 4>) = 0;
        void setPosSize(sf::Vector2f pos, sf::Vector2f size);
        const sf::Sprite& getSprite() const {return *sprite;};
        void setPos();
};

class Road : public Building {
    private:
        static bool areTexturesLoaded;
        static std::array<sf::Texture, 4> road_textures;
    public:
        Road(sf::Vector2f pos, sf::Vector2f size);
        ~Road() = default;
        static void load_textures(const std::string& straight, const std::string& corner, const std::string& intersection, const std::string& tshape);
        void update(std::array<Neighbor, 4>);
};

class House : public Building {
    private:
        // add house type or smth like that
    public:
        House(sf::Vector2f pos, sf::Vector2f size);
        ~House() = default;
        void update(std::array<Neighbor, 4>) {return;};
};
