#include <SFML/Graphics.hpp>
#include "Tile.h"

bool Tile::is_texture_loaded = false;
sf::Texture Tile::tileTexture;

void Tile::init_texture(const std::string &path) {
    if (!is_texture_loaded)
        tileTexture.loadFromFile(path, sf::IntRect(0, 0, 100, 100));
    is_texture_loaded = true;
}

Tile::Tile(sf::Vector2f pos, sf::Vector2f size) : pos(pos), size(size) {
    init_texture("assets/grass.png"); //TODO: move from constructor.
    tile->setSize(size);
    tile->setPosition(pos);
    tile->setTexture(&tileTexture);
    tile->setOutlineColor(sf::Color::Black);
};

void Tile::setState(Building_Current new_state) {
    if (new_state == state) return;

    state = new_state;
    if (new_state == Building_Current::Road) {
        building = std::make_unique<Road>(pos, size);
    }

    if (new_state == Building_Current::House) {
        building = std::make_unique<House>(pos, size);
    }

    if (new_state == Building_Current::None) {
        building = nullptr;
    }
}