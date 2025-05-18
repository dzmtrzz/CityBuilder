#include "UIElements.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <format>

sf::Font TextElement::m_font;

Button::Button(sf::Vector2f buttonPos, sf::Vector2f buttonDim, std::function<void(Game&)> onClick) : on_click(std::move(onClick)) {
    button->setPosition(buttonPos);
    button->setSize(buttonDim);
    button->setFillColor(sf::Color(173, 171, 163,255)); // gray
    button->setOutlineColor(sf::Color::Black);
}

void Button::init_texture(const std::string &path, sf::IntRect dimensions) {
    if (!texture.loadFromFile(path, dimensions)) {
        throw std::runtime_error("Failed to load texture");
    }

    button->setTexture(&texture);
}

void Button::update(bool is_selected) {
    if (is_selected) {
        button->setOutlineThickness(-2);
    } else {
        button->setOutlineThickness(0);
    }
}

void TextElement::load_font(const std::string& path) {
    m_font.loadFromFile(path);
}

TextElement::TextElement(const std::string &primary, const std::string &secondary, sf::Vector2f position) : primary_text(primary), secondary_text(secondary) {
    std::string text = std::format("{} {}", primary, secondary);
    m_text.setFont(m_font);
    m_text.setString(text);
    m_text.setPosition(position);
    m_text.setCharacterSize(14);
    m_text.setFillColor(sf::Color::Black);
}

void TextElement::update() {
    std::string text = std::format("{} {}", primary_text, secondary_text);
    m_text.setString(text);
}