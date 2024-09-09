#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

struct Widget : sf::Drawable
{
    protected:
        Widget() = default;
        virtual ~Widget() = default;
        
    public:
        virtual void draw(const std::string& message) = 0;
        virtual void handleEvent(const sf::Event& event) = 0;
        sf::Vector2f getPosition();
        sf::Vector2f getSize();

        Widget(const Widget&) = delete;
        Widget& operator = (const Widget&) = delete;

        template <typename ... Args>
        static std::shared_ptr<Widget> createButton(Args&& ... args);

    protected:
        sf::Vector2f position;
        sf::Vector2f size;
};