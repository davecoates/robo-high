#pragma once

#include <string>
#include <iostream>

#include "component.hpp"

namespace rh {

    class EntityManager;

    typedef unsigned int EntityID;

    class BaseNode {

        public:

            virtual ~BaseNode() { }

            virtual ComponentGroupIds get_group_ids() = 0;
            virtual ComponentMask get_component_mask() = 0;

            virtual void init() = 0;

    };

}
