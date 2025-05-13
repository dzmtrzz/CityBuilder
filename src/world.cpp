#include "Data_types.h"
#include "Game.h"
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <vector>
#include "Tile.h"

void Game::init_world(sf::Vector2f size) {
    sf::Vector2f TileSize = sf::Vector2f(size.x / tilesPerRow, size.y / tilesPerRow);
    for (float y = 0; y < size.y; y += TileSize.y) 
        for (float x = 0; x < size.x; x += TileSize.x)
            tileGrid.push_back(std::make_unique<Tile>(sf::Vector2f(x, y), TileSize));
}

// i am not proud of this implementation
std::array<Neighbor, 4> Game::get_neighbors(std::vector<std::unique_ptr<Tile>>::const_iterator iter) {
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