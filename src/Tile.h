#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include "Buildings.h"
#include "Data_types.h"
#include "VFX.h"

class Tile {
    private:
        std::unique_ptr<sf::RectangleShape> tile = std::make_unique<sf::RectangleShape>();

        static sf::Texture tileTexture;
        static bool is_texture_loaded;

        Building_Current state = Building_Current::None;
        std::unique_ptr<Building> building = nullptr;

        std::unique_ptr<TileEffect> effect = nullptr;
    public:
        static void init_texture(const std::string& path);

        explicit Tile(sf::Vector2f pos, sf::Vector2f size);

        void updateBuilding(const std::array<Neighbor, 4>& neighbor_tiles) {if (building != nullptr) building->update(neighbor_tiles);}
        void updateBuildingSize(sf::Vector2f size) {if (building != nullptr) building->updateSize(size);}
        void updateEffect() {if (effect != nullptr) {effect->update(); if (!effect->getShouldExist()) effect = nullptr;}}

        [[nodiscard]] Building_Current getState() const {return state;};
        void setState(Building_Current new_state); // make sure to change `building` along with state

        [[nodiscard]] const sf::Sprite& getBuildingSprite() const {return building->getSprite();};
        sf::RectangleShape& getTile() {return *tile;}

        [[nodiscard]] TileEffect* getTileEffect() const {return effect.get();}
        void setTileEffect() {effect = std::make_unique<Explosion>(tile->getSize());}
};