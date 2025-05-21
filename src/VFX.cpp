#include "VFX.h"
#include <SFML/Graphics.hpp>

sf::Texture Explosion::m_texture;

void Explosion::init_texture(const std::string& path) {
    if (!m_texture.loadFromFile(path)) {
        throw std::runtime_error("Failed to load explosion texture");
    }
}

Explosion::Explosion(sf::Vector2f size) {
    m_sprite.setTexture(m_texture);
    m_sprite.setScale({size.x / 100, size.y / 100});

}

void Explosion::update() {
    internal_time += internal_clock.restart();
    if (internal_time.asSeconds() >= 0.25) {
        shouldExist = false;
    }
}