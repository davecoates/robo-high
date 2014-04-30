#include "entity.hpp"
#include "entitymanager.hpp"
#include "system.hpp"

namespace rh {

    ///////////////////////////////////////////////////////////////////////////
    Entity EntityManager::create_entity() {
        auto id = generate_entity_id();

        return Entity(this, id); 
    }

    EntityID EntityManager::generate_entity_id() {
        auto id = next_entity_id_.fetch_add(1);
        if (component_masks_.size() <= id) {
            component_masks_.resize(id+1);
        }
        component_masks_[id] = 0;
        return id;
    }


    ///////////////////////////////////////////////////////////////////////////
    void EntityManager::process(sf::RenderWindow *window) {
        for (auto& system : systems_) {
            system->process(window);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    void EntityManager::init_component(const unsigned int& entity_id, BaseComponent* component) {
        for (auto& system : systems_) {
            system->init_component(entity_id, component);
        }
    }


    ///////////////////////////////////////////////////////////////////////////
    // Static member initialisation
    EntityManager::NodeFactories EntityManager::node_factories 
        = EntityManager::NodeFactories();

}
