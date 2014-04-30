#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "app.hpp"
#include "entitymanager.hpp"
#include "all_nodes.hpp"

int main()
{
    auto app = std::unique_ptr<rh::Application>(new rh::Application());


    rh::EntityManager::register_node<rh::PhysicsNode>();
    rh::EntityManager::register_node<rh::RenderNode>();
    rh::EntityManager::register_node<rh::MovementNode>();

    app->init("Robo High", rh::SCREEN_RESOLUTION_W, rh::SCREEN_RESOLUTION_H, 32, false);
    app->run();

    return 0;
}
