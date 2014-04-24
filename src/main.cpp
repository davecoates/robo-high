#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "app.hpp"
#include "entitymanager.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/physics.hpp"
#include <iostream>

int main()
{
/*    std::cout << "Hi\n";*/
    //auto em = RH::EntityManager::get_instance();
    //auto id = em->generate_entity();
    //em->add_component<RHComponents::Position>(id, 3, 5);
    //em->add_component<RHComponents::Physics>(id, 8, 8);
    //auto pos = em->get_component<RHComponents::Position>(id);
    //std::cout << pos->x << " " << pos->y << '\n';
    //pos->x = 5;
    //pos = em->get_component<RHComponents::Position>(id);
    //std::cout << pos->x << " " << pos->y << "\n";
    //em->add_component<RHComponents::Renderable>(id);
    //RHComponents::Position *p1 = nullptr;
    //RHComponents::Physics *p2 = nullptr;
    //RHComponents::Renderable *p3 = nullptr;
    //auto has_all = em->get_components<RHComponents::Position, RHComponents::Physics, RHComponents::Renderable>(id, p1, p2, p3);
    //std::cout << "Has all? " << has_all << std::endl;
    /*std::cout << p1->x << " " << p1->y << " " << p2->x << " " << p2->y << std::endl;*/
    auto app = RH::Application::get_instance();

    app->init("Robo High", RH::SCREEN_RESOLUTION_W, RH::SCREEN_RESOLUTION_H, 32, true);
    app->run();

    
    return 0;
}
