#include "physicsnode.hpp"
#include "entitymanager.hpp"

namespace rh {

    void PhysicsNode::init(EntityManager* em, EntityID entity_id) {
        physics_ = em->get_component<components::Physics>(entity_id); 
        transformable_  = em->get_component<components::Transformable>(entity_id); 
    }

    static auto _ = EntityManager::register_node<PhysicsNode>();
}
