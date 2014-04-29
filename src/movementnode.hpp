#pragma once

#include "node.hpp"
#include "components/movement.hpp"
#include "components/physics.hpp"

namespace rh {

    struct MovementNode : public Node<components::Movement, components::Physics> {

        using Node::Node;

        components::Movement *movement_;
        components::Physics *physics_;

        std::string get_type() { return "Render"; }

        void init(EntityManager* em, EntityID entity_id);

    };

}
