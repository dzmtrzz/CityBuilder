
enum class Direction {
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
    const Direction direction;
    const Building_Current building;
};
