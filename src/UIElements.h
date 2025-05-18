#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include <memory>

class Game; //this feels wrong


class UIElement {
    public:
        virtual ~UIElement() = default;
        [[nodiscard]] virtual sf::Drawable& get_drawable() = 0;
        // virtual void update() = 0;
};

class TextElement : public UIElement {
    private:
        sf::Text m_text;
        static sf::Font m_font;

        std::string primary_text;
        std::string secondary_text;
    public:
        static void load_font(const std::string& path);
        explicit TextElement(const std::string& primary, const std::string& secondary, sf::Vector2f position);

        void setPrimaryText(const std::string& text) {primary_text = text;}
        void setSecondaryText(const std::string& text) {secondary_text = text;}

        void update();

        [[nodiscard]] sf::Drawable& get_drawable() override {return m_text;}
};

class Button : public UIElement {
    private:
        std::unique_ptr<sf::RectangleShape> button = std::make_unique<sf::RectangleShape>();
        sf::Texture texture;
        std::function<void(Game&)> on_click;

    public:
        explicit Button(sf::Vector2f buttonPos, sf::Vector2f buttonDim, std::function<void(Game&)> on_click);
        void init_texture(const std::string& path, sf::IntRect dimensions);

        [[nodiscard]] sf::Drawable& get_drawable() {return *button;}
        [[nodiscard]] sf::RectangleShape& get_shape() const {return *button;}

        void click(Game& game) {on_click(game);}
        void update(bool is_selected);
};