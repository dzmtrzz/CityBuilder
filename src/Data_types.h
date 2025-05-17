#pragma once
#include <vector>
#include <memory>
class Tile;

enum class Direction {
    Null,
    Left,
    Right,
    Up,
    Down
};

enum class Building_Current {
    None,
    Road,
    House
};

struct Neighbor {
    Direction direction;
    // Building_Current building;
    Tile *tile = nullptr;
    std::vector<std::unique_ptr<Tile>>::const_iterator it;
};
