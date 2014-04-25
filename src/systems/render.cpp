#include "render.hpp"
#include "../components.hpp"
#include "../entitymanager.hpp"

namespace rh {

    void RenderSystem::process(sf::RenderWindow *window) {
        auto em = EntityManager::get_instance();
        for (auto entity_id : em->get_entities()) {

            auto renderable = em->get_component<rh::components::Renderable>(entity_id);
            if (renderable) {
                window->draw(*renderable->drawable);
            }
        }
    }

}
