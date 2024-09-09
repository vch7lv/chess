#include <SFML/Graphics.hpp>
#include "Callback.h"
#include <iostream>

struct sum
{
    void operator () (int a, int b, int c) const
    {
        std::cout << a+b+c << std::endl;
    }
};

void f (int a, int b, int c) {std::cout << a << ' ' << b << ' ' << c << std::endl;}

int main()
{
    auto p = createCallback(&f, 1, 2, 3);
    p->invoke();
}git