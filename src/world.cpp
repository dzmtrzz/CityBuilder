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
#include <string>
#include <vector>
#include "Tile.h"



bool Road::areTexturesLoaded = false;
std::array<sf::Texture, 4> Road::road_textures;

void Road::load_textures(const std::string &straight, const std::string &corner, const std::string &intersection, const std::string &tshape) {
    sf::IntRect area = sf::IntRect(0, 0, 100, 100);
    if (!areTexturesLoaded) {
        road_textures[0].loadFromFile(straight, area);
        road_textures[1].loadFromFile(corner, area);
        road_textures[2].loadFromFile(tshape, area);
        road_textures[3].loadFromFile(intersection, area);
        areTexturesLoaded = true;
    }
}

void Road::update(std::array<Neighbor, 4> arr) {
    char neighborRoads = 0;
    std::array<char, 4> directions = {0,0,0,0};

    for (Neighbor& n : arr) {
        if (n.direction != Direction::Null) {
            if (n.building == Building_Current::Road) {
                neighborRoads++;
                directions[static_cast<char>(n.direction) - 1] = static_cast<char>(n.direction); // Directions are in the form of [left, right, up, down], if direction[0] == 0 - no road on the left. otherwise yes road on the left. 
            }
        }
        
    }

    load_textures("road-s.png", "road-c.png", "road-4.png", "road-3.png");

    if (neighborRoads == 4) {
        sprite->setTexture(road_textures[3]); 
    }

    else if (neighborRoads == 3) {
        sprite->setTexture(road_textures[2]); //tshape
        if (directions[3] != 0 && directions[2] == 0) // if road down and no road up rotate 270
            sprite->setRotation(90*3);
        else if (directions[2] != 0 && directions[3] == 0) // if inverse rotate 90
            sprite->setRotation(90);
        else if (directions[0] != 0) // if road on the left (but no road on the right because thats impossible) rotate 180 
            sprite->setRotation(90*2);
        else
            sprite->setRotation(0);
    }

    else if (neighborRoads == 2) {
        if (directions[0] != 0 && directions[1] != 0) {
            sprite->setTexture(road_textures[0]); // straight
            sprite->setRotation(90);
        } else if (directions[2] != 0 && directions[3] != 0) {
            sprite->setTexture(road_textures[0]);
        } else if (directions[2] != 0 && directions[1] != 0) { // U/R
            sprite->setTexture(road_textures[1]); // corner
        } else if (directions[2] != 0 && directions[0] != 0) { // U/L
            sprite->setTexture(road_textures[1]);
            sprite->setRotation(90);
        } else if (directions[0] != 0 && directions[3] != 0) { // L/D
            sprite->setTexture(road_textures[1]);
            sprite->setRotation(90*2);
        } else {                                               // R/D
            sprite->setTexture(road_textures[1]);
            sprite->setRotation(90*3);
        }
    }

    else {
        sprite->setTexture(road_textures[0]);
    }
}

Road::Road(sf::Vector2f pos, sf::Vector2f size) {
    tilePos = pos; tileSize = size;


    sprite->setPosition(pos);
    sprite->setScale({size.x / 100, size.y / 100});
//    sprite->setOrigin({size.x/2, size.y/2}); 
//    sprite->setRotation((90*(random()%4))); 
}

House::House(sf::Vector2f pos, sf::Vector2f size) {
    tilePos = pos; tileSize = size;
    
    //TODO: move out of constructor, probably make a static(?) | maybe a static array for different house textures?
    texture = std::make_shared<sf::Texture>();
    texture->loadFromFile("house.png", sf::IntRect(0, 0, 100, 100));
    

    sprite->setTexture(*texture);
    sprite->setPosition(pos);
    sprite->setScale({size.x / texture->getSize().x, size.y / texture->getSize().y});
//    sprite->setOrigin({size.x/2, size.y/2}); 
//    sprite->setRotation((90*(random()%4))); 

    //update(std::array<Neighbor, 4>) // yea
}



void GameWorld::init_world(sf::Vector2f size) {
    sf::Vector2f TileSize = sf::Vector2f(size.x / tilesPerRow, size.y / tilesPerRow);
    for (float y = 0; y < size.y; y += TileSize.y) 
        for (float x = 0; x < size.x; x += TileSize.x)
            tileGrid.push_back(std::make_unique<Tile>(sf::Vector2f(x, y), TileSize));
}

// i am not proud of this implementation
std::array<Neighbor, 4> GameWorld::get_neighbors(std::vector<std::unique_ptr<Tile>>::const_iterator iter) const {
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