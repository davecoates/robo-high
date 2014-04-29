#include "entitymanager.hpp"
#include "entity.hpp"
#include "system.hpp"

namespace rh {

    Entity EntityManager::create_entity() {
        auto id = generate_entity_id();

        return Entity(this, id); 
    }

    // TODO: This is really quite bad... creating entity object every frame for
    // each entity
    const EntityVector EntityManager::get_entities() { 
        EntityVector entities;
        for (uint i=0;i<component_masks_.size();i++) {
            entities.push_back(Entity(this, i));
        }
        return entities; 
    }


    void EntityManager::process(sf::RenderWindow *window) {
        auto entities = get_entities();
        for (auto& system : systems_) {
            system->process(window);
        }
    }

    void EntityManager::init_component(const unsigned int& entity_id, BaseComponent* component) {
        for (auto& system : systems_) {
            system->init_component(entity_id, component);
        }
    }

   std::vector<EntityManager::NodeRegistration> EntityManager::node_factories = std::vector<EntityManager::NodeRegistration>();

}
