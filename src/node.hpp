#pragma once

#include "component.hpp"
#include "components.hpp"

#include "entity.hpp"
#include "basenode.hpp"

#include <vector>
#include <iostream>
#include <iterator>

namespace rh {

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

        template <typename T>
        static ComponentGroupIds get_group_ids() {
            ComponentGroupIds group_ids;
            group_ids.push_back(Component<T>::get_group_id());

            return group_ids;
        }

        // Get vector of component group_ids that make up this node
        template <typename T1, typename T2, typename ... Ts>
        static ComponentGroupIds get_group_ids() {
            auto group_ids = get_group_ids<T1>();
            auto group_ids_tmp = get_group_ids<T2, Ts...>();
            group_ids.insert(group_ids.end(),
                    std::make_move_iterator(group_ids_tmp.begin()),
                    std::make_move_iterator(group_ids_tmp.end()));

            return group_ids;
        }


        protected:
            Entity entity_;

        public:


        virtual void init() = 0;

        explicit Node(Entity entity) : entity_(entity) {}

        EntityID get_entity_id() { return entity_.id(); }

        Entity get_entity() { return entity_; }

        ComponentMask get_component_mask() override {
            return Node<C1, Cs...>::get_mask();
        }

        static ComponentMask get_mask() {
            static auto mask = get_mask<C1, Cs...>();
            return mask;
        }

        ComponentGroupIds get_group_ids() override {
            static ComponentGroupIds group_ids = get_group_ids<C1, Cs...>();

            return group_ids;
        }

    };



}

