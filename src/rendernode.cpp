#include "rendernode.hpp"
#include "entitymanager.hpp"

namespace rh {

    void RenderNode::init(EntityManager* em, EntityID entity_id) {
        renderable_ = em->get_component<components::Renderable>(entity_id); 
        transformable_  = em->get_component<components::Transformable>(entity_id); 
    }


    static auto _ = EntityManager::register_node<RenderNode>();
}
