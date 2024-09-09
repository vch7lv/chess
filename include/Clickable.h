#pragma once
#include "Widget.h"
#include "Callback.h"

struct Clickable : public Widget
{
    std::unique_ptr<CallbackBase> onPressed;
    std::unique_ptr<CallbackBase> onReleased; 
    std::unique_ptr<CallbackBase> onHover;
};