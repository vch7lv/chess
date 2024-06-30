#pragma once
#include <SFML/Window.hpp>
#include <memory>
#include <list>
#include "Widget.h"


struct Gui
{
    public:
        void handleEvent(const sf::Event& event);
        void removeWidget(const std::string& ID);
        void addWidget(std::shared_ptr<Widget> widget);
        void activateWidget(const std::string& ID);
        void draw() const;
    private:
        std::list<std::shared_ptr<Widget>> widgets;
        std::shared_ptr<Widget> activeWidget;
};