#pragma once

#include "component.hpp"
#include "components.hpp"

#include <iostream>

namespace rh {

    class BaseNode {

        public:
            virtual ~BaseNode() {}

            virtual std::string get_type() = 0;

    };

    template <typename C1,  typename ... Cs>
    class Node : public BaseNode {

        template <typename T>
        static ComponentMask get_mask() {
            auto group_id = Component<T>::get_group_id();
            ComponentMask mask = 1 << group_id;
            return mask;
        }

        /**
         * We recursively reduce until we have a single template argument
         * which is handled above.
         *
         * @see create_component_mask() above
         */
        template <typename T1, typename T2, typename ... Ts>
        static ComponentMask get_mask() {
            return get_mask<T1>() | get_mask<T2, Ts...>();
        }

        public:

        static ComponentMask get_mask() {
            static auto mask = get_mask<C1, Cs...>();
            return mask;
        }

    };

    struct PositionNode : public Node<components::Transformable> {

        std::string get_type() { return "Position"; }


    };


    struct RenderNode : public Node<components::Renderable, components::Transformable> {

std::string get_type() { return "Render"; }

    };

    struct PhysicsNode : public Node<components::Physics, components::Transformable> {

std::string get_type() { return "Physics"; }

    };


    // How about
    /*
     *
    class System<typename N1, typename ... Ns> {
        
        static std::vector<ComponentMask> get_component_mask() {
        }

    }

    class RenderSystem<RenderNode> {
    }
     */
}

