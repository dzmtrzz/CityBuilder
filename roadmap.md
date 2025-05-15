## Beginning
### Main goal:
- [x] Generate a basic map while accounting for stuff needed later.
#### Checklist (for main goal):
- [x] virtual class for generic building called `Building`, containing
    - [x] unique ptr to `sf::Drawable obj` (probably another square) **OR** inherit the class from sf::Drawable, sf::Transformable
    - [x] `virtual void update() = 0;`
        - [x] takes an array of 4 structs as argument, 
            - [x] each struct consists of
                - [x] neighbor's enum `neighbor_direction` (left, right, up, down)
                - [x] neighbor's building type (`current_state` from `Tile`)
        - [x] updates the sprite of `obj` accordingly (or doesn't do anything)

- [x] Class Building will be used for:
    - [x] Roads
    - [x] Houses

- [x] Class `Tile` consisting of 
    - [x] a `sf::RectangleShape`
    - [x] an `enum current_state`(empty/road/house)
    - [x] unique ptr to `Building building` (initialised with nullptr)
    - [x] `void update()` that calls the update method of `building`, takes the same vector as `update()` from `Building`.
    - [x] setter for `building` (make sure to set current_state appropriately)

- [x] Game class
    - [x] Currently will contain basically boilerplate code
    - [x] Will have an array of (n*n) unique pointers to `Tile` objects (a vector because an array turned out to be impossible)
        - [x] n will be defined in the constructor
    - [x] Method init_world() that
        - [x] Generates a grid of `Tile` objects by
            - take a general square area (for example 640 by 640 pixels)
            - take n amount of subdivisions
            - int l = $\frac{640}{n}$ will be length of a side
            - int g = 0
            - for (int m = 0; m < 640; m+l)
                - for (int i = 0; i < 640; i+l)
                    - generate square with cordinates x=i, y=g

    - [x] enum build_state containing currently selected building to be placed
        - [x] None (initialised as)
        - [x] House
        - [x] Road

## Post-beginning things
These are the things that will be done after everything above. 
- [x] Game class
    - [x] Logic
        - [x] Add logic for highlighting the tile mouse is hovering over
        - [x] On mouse click, if hovering over a tile create the appropriate building.
        - [x] Add ability to switch between the states of `build_state` 

    - [x] Write a member function that checks tiles near a tile `get_neighbors(shared_ptr tile)` (used an iterator)
        - [x] returns an array of 4 structs mentioned in the `Building` class's `update()` function.
        - [x] Use for `Tile::update()`

- [x] Roads
    - [x] Implement `update()`
        - [x] SHOULD connect roads

- [x] Houses
    - [x] `update()` shouldn't do anything yet.

- [x] Render
    - [x] Should render objects in the following order:
        - Tiles
        - Roads
        - Houses

## Post-post-beginning things
idk
