#pragma once

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
    House,
};

struct Neighbor {
    Direction direction;
    Building_Current building;
};
