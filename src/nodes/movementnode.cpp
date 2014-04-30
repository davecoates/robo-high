#include "movementnode.hpp"
#include "../entitymanager.hpp"

namespace rh {

    using namespace components;

    void MovementNode::init() {
        entity_.get_components<Movement, Physics>(movement_, physics_);
    }

}
