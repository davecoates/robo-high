#include "render.hpp"
#include "../components.hpp"
#include "../entitymanager.hpp"
#include <iostream>

namespace rh {

    void RenderSystem::process(sf::RenderWindow *window) {
        /*for (auto entity : entities) {*/

            //auto renderable = entity.get_component<rh::components::Renderable>();
            //if (renderable) {
                //if (renderable->drawable) {
                    //window->draw(*renderable->drawable);
                //} else {
                    //// TODO: Logger
                    //std::cout << "WARNING: No drawable defined\n";
                //}
            //}
        /*}*/
    }

}
