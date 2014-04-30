#include "rendernode.hpp"
#include "../entitymanager.hpp"

namespace rh {

    using namespace components;

    void RenderNode::init() {
        entity_.get_components<Renderable, Transformable>(renderable_, transformable_);
    }

}
