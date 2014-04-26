#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "app.hpp"
#include <iostream>

int main()
{
    auto app = std::unique_ptr<rh::Application>(new rh::Application());

    app->init("Robo High", rh::SCREEN_RESOLUTION_W, rh::SCREEN_RESOLUTION_H, 32, true);
    app->run();

    return 0;
}
