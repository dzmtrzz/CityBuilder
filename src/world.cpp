#include "Data_types.h"
#include "Game.h"
#include <algorithm>
#include <array>
#include <memory>
#include <vector>
#include "Tile.h"


void GameWorld::init_world(sf::Vector2f size) {
    sf::Vector2f TileSize = sf::Vector2f(std::min(size.x / tilesPerRow, size.y / numRows), std::min(size.x / tilesPerRow, size.y / numRows));
    if (TileSize.x < 74)
        TileSize = {74, 74};
    for (int y = 0; y < numRows; y += 1)
        for (int x = 0; x < tilesPerRow; x += 1)
            tileGrid.push_back(std::make_unique<Tile>(sf::Vector2f(x*TileSize.x, y*TileSize.y), TileSize));
}

// i am not proud of this implementation
std::array<Neighbor, 4> GameWorld::get_neighbors(std::vector<std::unique_ptr<Tile>>::const_iterator iter) const { //theres a weird bug where at 50*x + 25 neighboring tiles are offset by x+1, this function is probably the culprit
    int idx = static_cast<int>(iter - tileGrid.begin());

    std::array<Neighbor, 4> arr;
    std::fill(arr.begin(), arr.end(), Neighbor{Direction::Null, nullptr, tileGrid.end()});

    if ((idx%tilesPerRow) < tilesPerRow-1) {
        arr[0] = Neighbor{Direction::Right, (iter+1)->get(), (iter+1)};
    }
    if ((idx%tilesPerRow) != 0) {
        arr[1] = Neighbor{Direction::Left, (iter-1)->get(), (iter-1)};
    }
    if (idx >= tilesPerRow) {
        arr[2] = Neighbor{Direction::Up, (iter-tilesPerRow)->get(), (iter-tilesPerRow)};
    }
    if (idx <= (tilesPerRow*numRows-tilesPerRow-1)) {
        arr[3] = Neighbor{Direction::Down, (iter+tilesPerRow)->get(), (iter+tilesPerRow)};
    }


    return arr;
}