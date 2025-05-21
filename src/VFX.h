#pragma once
#include <SFML/Graphics.hpp>

class TileEffect {
    protected:
        bool shouldExist = true;
    public:
        virtual ~TileEffect() = default;
        [[nodiscard]] bool getShouldExist() const {return shouldExist;}
        virtual sf::Drawable& get_drawable() = 0;
        virtual void update() = 0;
};

class Explosion : public TileEffect {
    private:
        sf::Sprite m_sprite;
        static sf::Texture m_texture;
        sf::Clock internal_clock;
        sf::Time internal_time = sf::Time::Zero;
    public:
        Explosion(sf::Vector2f size);
        static void init_texture(const std::string& path);
        sf::Drawable& get_drawable() override {return m_sprite;}
        void update() override;
};