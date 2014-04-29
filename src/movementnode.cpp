#include "movementnode.hpp"
#include "entitymanager.hpp"

namespace rh {

    void MovementNode::init(EntityManager* em, EntityID entity_id) {
        movement_ = em->get_component<components::Movement>(entity_id); 
        physics_  = em->get_component<components::Physics>(entity_id); 
    }


    static auto _ = EntityManager::register_node<MovementNode>();
}
