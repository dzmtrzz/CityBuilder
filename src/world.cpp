#include "Buildings.h"
#include "Data_types.h"
#include "Game.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <vector>
#include "Tile.h"



bool Tile::is_texture_loaded = false;
sf::Texture Tile::tileTexture;

void Tile::init_texture(const std::string &path) {
    if (!is_texture_loaded)
        tileTexture.loadFromFile(path, sf::IntRect(0, 0, 100, 100));
    is_texture_loaded = true;
}

Tile::Tile(sf::Vector2f pos, sf::Vector2f size) : pos(pos), size(size) {
    init_texture("grass.png");
    tile->setSize(size);
    tile->setPosition(pos);
    tile->setTexture(&tileTexture);
    tile->setOutlineColor(sf::Color::Black);
};

House::House(sf::Vector2f pos, sf::Vector2f size) {
    tilePos = pos; tileSize = size;
    
    //TODO: move out of constructor, probably make a static(?) | maybe a static array for different house textures?
    texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("house.png", sf::IntRect(0, 0, 100, 100));
    

    sprite->setTexture(*texture);
    sprite->setPosition(pos);
    sprite->setScale({tileSize.x / texture->getSize().x, tileSize.y / texture->getSize().y});
//    sprite->setOrigin({size.x/2, size.y/2}); 
//    sprite->setRotation((90*(random()%4))); 

    //update(std::array<Neighbor, 4>) // yea
}

void Tile::setState(Building_Current new_state) {
    if (new_state == state) return;

    state = new_state;
    // if (new_state == Building_Current::Road) {
    //     building = std::make_unique<Road>(pos, size);
    // }

    if (new_state == Building_Current::House) {
        building = std::make_unique<House>(pos, size);
    }

    if (new_state == Building_Current::None) {
        building = nullptr;
    }
}

void Game::init_world(sf::Vector2f size) {
    sf::Vector2f TileSize = sf::Vector2f(size.x / tilesPerRow, size.y / tilesPerRow);
    for (float y = 0; y < size.y; y += TileSize.y) 
        for (float x = 0; x < size.x; x += TileSize.x)
            tileGrid.push_back(std::make_unique<Tile>(sf::Vector2f(x, y), TileSize));
}

// i am not proud of this implementation
std::array<Neighbor, 4> Game::get_neighbors(std::vector<std::unique_ptr<Tile>>::const_iterator iter) const {
    int idx = static_cast<int>(iter - tileGrid.begin());

    std::array<Neighbor, 4> arr;
    std::fill(arr.begin(), arr.end(), Neighbor{Direction::Null, Building_Current::None});

    if ((idx%tilesPerRow) < tilesPerRow-1) {
        arr[0] = Neighbor{Direction::Right, (iter+1)->get()->getState()};
    }
    if ((idx%tilesPerRow) != 0) {
        arr[1] = Neighbor{Direction::Left, (iter-1)->get()->getState()};
    }
    if (idx >= tilesPerRow) {
        arr[2] = Neighbor{Direction::Up, (iter-tilesPerRow)->get()->getState()};
    }
    if (idx <= (tilesPerRow*tilesPerRow-tilesPerRow-1)) {
        arr[3] = Neighbor{Direction::Down, (iter+tilesPerRow)->get()->getState()};
    }


    return arr;
}