#pragma once

#include "node.hpp"
#include "components/renderable.hpp"
#include "components/transformable.hpp"

namespace rh {

    struct RenderNode : public Node<components::Renderable, components::Transformable> {

        using Node::Node;

        components::Renderable *renderable_;
        components::Transformable *transformable_;

        std::string get_type() { return "Render"; }

        void init(EntityManager* em, EntityID entity_id);

    };

}
