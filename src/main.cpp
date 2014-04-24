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
    //auto em = rh::EntityManager::get_instance();
    //auto id = em->generate_entity();
    //em->add_component<rh::components::Position>(id, 3, 5);
    //em->add_component<rh::components::Physics>(id, 8, 8);
    //auto pos = em->get_component<rh::components::Position>(id);
    //std::cout << pos->x << " " << pos->y << '\n';
    //pos->x = 5;
    //pos = em->get_component<rh::components::Position>(id);
    //std::cout << pos->x << " " << pos->y << "\n";
    //em->add_component<rh::components::Renderable>(id);
    //rh::components::Position *p1 = nullptr;
    //rh::components::Physics *p2 = nullptr;
    //rh::components::Renderable *p3 = nullptr;
    //auto has_all = em->get_components<rh::components::Position, rh::components::Physics, rh::components::Renderable>(id, p1, p2, p3);
    //std::cout << "Has all? " << has_all << std::endl;
    /*std::cout << p1->x << " " << p1->y << " " << p2->x << " " << p2->y << std::endl;*/
    auto app = rh::Application::get_instance();

    app->init("Robo High", rh::SCREEN_RESOLUTION_W, rh::SCREEN_RESOLUTION_H, 32, true);
    app->run();

    
    return 0;
}
