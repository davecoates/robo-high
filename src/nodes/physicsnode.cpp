#include "physicsnode.hpp"
#include "../entitymanager.hpp"

namespace rh {

    using namespace components;

    void PhysicsNode::init() {
        entity_.get_components<Physics, Transformable>(physics_, transformable_);
    }

}
