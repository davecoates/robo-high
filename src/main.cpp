#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "app.hpp"

int main()
{
    auto app = RH::Application::get_instance();

    app->init("Robo High", RH::SCREEN_RESOLUTION_W, RH::SCREEN_RESOLUTION_H, 32, true);
    app->run();

    
    return 0;
}
