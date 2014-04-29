#include "node.hpp"
#include "entitymanager.hpp"

namespace rh {

    // Why do I have to do this? calling without assigning results in error
    auto a = EntityManager::register_node<RenderNode>();
    auto b = EntityManager::register_node<PhysicsNode>();
    auto c = EntityManager::register_node<PositionNode>();

}
