#include "Widget.h"
#include "Clickable.h"
#include <string>

struct Button final : public Clickable
{
    std::string text;
    sf::Color backgroundColor;
    sf::Color textColor;
};
//... recheck all
template <typename ... Args>
std::shared_ptr<Widget> createButton(Args&& ... args)
{
    return nullptr;
}