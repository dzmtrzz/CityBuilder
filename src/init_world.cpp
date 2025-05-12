#include "Game.h"
#include <SFML/System/Vector2.hpp>
#include <memory>
#include "Tile.h"

void Game::init_world(sf::Vector2f size) {
    sf::Vector2f TileSize = sf::Vector2f(size.x / tilesPerRow, size.y / tilesPerRow);
    for (float y = 0; y < size.y; y += TileSize.y) 
        for (float x = 0; x < size.x; x += TileSize.x)
            tileGrid.push_back(std::make_unique<Tile>(sf::Vector2f(x, y), TileSize));
}