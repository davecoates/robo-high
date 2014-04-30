#pragma once

#include "../node.hpp"
#include "../components/physics.hpp"
#include "../components/transformable.hpp"

namespace rh {

    struct PhysicsNode : public Node<components::Physics, components::Transformable> {

        using Node::Node;

        components::Physics *physics_;
        components::Transformable *transformable_;

        void init();

    };

}
