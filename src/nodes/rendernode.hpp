#pragma once

#include "../node.hpp"
#include "../components/renderable.hpp"
#include "../components/transformable.hpp"

namespace rh {

    struct RenderNode : public Node<components::Renderable, components::Transformable> {

        using Node::Node;

        components::Renderable *renderable_;
        components::Transformable *transformable_;

        void init();

    };

}
