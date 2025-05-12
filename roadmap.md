## Beginning
### Main goal:
- [ ] Generate a basic map while accounting for stuff needed later.
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

- [ ] Class `Tile` consisting of 
    - [ ] a `sf::RectangleShape`
    - [ ] an `enum current_state`(empty/road/house)
    - [ ] unique ptr to `Building building` (initialised with nullptr)
    - [ ] `void update()` that calls the update method of `building`, takes the same vector as `update()` from `Building`.
    - [ ] setter for `building` (make sure to set current_state appropriately)

- [ ] Game class
    - [ ] Currently will contain basically boilerplate code
    - [ ] Will have an array of (n*n) unique pointers to `Tile` objects
        - [ ] n will be defined in the constructor
    - [ ] Method init_world() that
        - [ ] Generates a grid of `Tile` objects by
            - take a general square area (for example 640 by 640 pixels)
            - take n amount of subdivisions
            - int l = $\frac{640}{n}$ will be length of a side
            - int g = 0
            - for (int m = 0; m > 640; m+l)
                - for (int i = 0; i > 640; i+l)
                    - generate square with cordinates x=i, y=g

    - [ ] enum build_state containing currently selected building to be placed
        - [ ] None (initialised as)
        - [ ] House
        - [ ] Road

## Post-beginning things
These are the things that will be done after everything above. 
- [ ] Game class
    - [ ] Logic
        - [ ] Add logic for highlighting the tile mouse is hovering over
        - [ ] On mouse click, if hovering over a tile create the appropriate building.
        - [ ] Add ability to switch between the states of `build_state` 

    - [ ] Write a member function that checks tiles near a tile `get_neighbors(shared_ptr tile)`
        - [ ] returns an array of 4 structs mentioned in the `Building` class's `update()` function.
        - [ ] Use for `Tile::update()`

- [ ] Roads
    - [ ] Implement `update()`
        - [ ] SHOULD connect roads

- [ ] Houses
    - [ ] `update()` shouldn't do anything yet.

- [ ] Render
    - [ ] Should render objects in the following order:
        - Tiles
        - Roads
        - Houses

## Post-post-beginning things
This is basically the final step, it's definitely the hardest one and probably the final one, unless i want to implement terrain generation at some point
- [ ] Implement a 2.5D perspective, like in OpenTTD. (Dimetric projection, but no need for rendering the sides of tiles, only the top.)
    - [ ] WILL likely require a rewrite of `Game::get_neighbors()`
    - [ ] WILL require VERY different positioning of the `Building` drawables.
    - [ ] WILL DEFINITELY require a bit of messing with it to get mouse detection working fine

- [ ] Take a look at/Add OpenGFX from OpenTTD for buildings, roads, tiles. 
