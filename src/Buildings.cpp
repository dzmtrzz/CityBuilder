#include "Buildings.h"
#include "Tile.h"


bool Road::areTexturesLoaded = false;
std::array<sf::Texture, 4> Road::road_textures;

sf::Texture House::texture;

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
            if (n.tile->getState() == Building_Current::Road) {
                neighborRoads++;
                directions[static_cast<char>(n.direction) - 1] = static_cast<char>(n.direction); // Directions are in the form of [left, right, up, down], if direction[0] == 0 - no road on the left. otherwise yes road on the left. 
            }
        }
        
    }

    load_textures("assets/road-s.png", "assets/road-c.png", "assets/road-4.png", "assets/road-3.png");

    if (neighborRoads == 4) {
        sprite->setTexture(road_textures[3]); 
    }

    else if (neighborRoads == 3) {
        sprite->setTexture(road_textures[2]); //tshape
        if (directions[2] != 0 && directions[3] == 0) // if road down and no road up rotate 270
            sprite->setRotation(90*3);
        else if (directions[3] != 0 && directions[2] == 0) // if inverse rotate 90
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
            sprite->setRotation(0);
        } else if (directions[2] != 0 && directions[1] != 0) { // U/R
            sprite->setTexture(road_textures[1]); // corner
            sprite->setRotation(0);
        } else if (directions[2] != 0 && directions[0] != 0) { // U/L
            sprite->setTexture(road_textures[1]);
            sprite->setRotation(90*3);
        } else if (directions[0] != 0 && directions[3] != 0) { // L/D
            sprite->setTexture(road_textures[1]);
            sprite->setRotation(90*2);
        } else {                                               // R/D
            sprite->setTexture(road_textures[1]);
            sprite->setRotation(90);
        }
    }

    else if (neighborRoads == 1) {
        sprite->setTexture(road_textures[0]);
        if (directions[0] != 0 || directions[1] != 0) {
            sprite->setRotation(90);
        } else {
            sprite->setRotation(0);
        }
    }

    else {
        sprite->setTexture(road_textures[0]);
    }



    sprite->setOrigin(sprite->getLocalBounds().width/2, sprite->getLocalBounds().height/2); 

}

Road::Road(sf::Vector2f size) {
    tileSize = size;

    sprite->setPosition({size.x/2, size.y/2});
    sprite->setScale({size.x / 100, size.y / 100});
}

void House::init_texture(const std::string& path) {
    if (!texture.loadFromFile(path)) {
        throw std::runtime_error("Could not load house texture");
    }
}

House::House(sf::Vector2f size) {
    tileSize = size;

    sprite->setTexture(texture);
    sprite->setPosition({size.x/2, size.y/2});
    sprite->setScale({size.x / 100, size.y / 100});
    sprite->setOrigin(sprite->getLocalBounds().width/2, sprite->getLocalBounds().height/2);
    sprite->setRotation((90*(random()%4))); 

    //update(std::array<Neighbor, 4>) // yea
}
