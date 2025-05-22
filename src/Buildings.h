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
        sf::Vector2f tileSize;
    public:
        virtual ~Building() = default;
        virtual void update(std::array<Neighbor, 4>) = 0;
        void updateSize(sf::Vector2f size) {sprite->setScale({size.x / 100, size.y / 100}); sprite->setPosition({size.x/2, size.y/2});}
        [[nodiscard]] const sf::Sprite& getSprite() const {return *sprite;}
        void setPos();
};

class Road : public Building {
    private:
        static bool areTexturesLoaded;
        static std::array<sf::Texture, 4> road_textures;
    public:
        Road(sf::Vector2f size);
        static void load_textures(const std::string& straight, const std::string& corner, const std::string& intersection, const std::string& tshape);
        void update(std::array<Neighbor, 4>) override;
};

class House : public Building {
    private:
        static sf::Texture texture;
    public:
        static void init_texture(const std::string& path);
        House(sf::Vector2f size);
        void update(std::array<Neighbor, 4>) override {}
};
