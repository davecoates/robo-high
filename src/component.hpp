#pragma once

#include <bitset>
#include <vector>
#include <iostream>
#include "constants.hpp"

namespace rh {

    typedef unsigned int ComponentGroupId;

    typedef std::bitset<rh::MAX_COMPONENTS> ComponentMask;
    typedef std::vector<ComponentGroupId> ComponentGroupIds;


    /**
     * Base class exists to track group counter
     */
    class BaseComponent
    {
        public:
            BaseComponent() {};
            virtual ~BaseComponent() { };
        protected:
            static ComponentGroupId group_id_counter_;
    };


    /**
     * New components should extend this class
     */
    template <typename T>
    class Component : public BaseComponent
    {
        public:
            static  ComponentGroupId get_group_id();
        private:
            // Group ID for components of type T
            static ComponentGroupId group_id;

    };

    template <typename T>
    ComponentGroupId Component<T>::get_group_id() {
        static ComponentGroupId group_id = group_id_counter_++;
        return group_id;
    }

}
