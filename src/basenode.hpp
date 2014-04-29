#pragma once

#include <string>

#include "component.hpp"

namespace rh {

    class EntityManager;

    typedef unsigned int EntityID;

    class BaseNode {

        public:

            virtual ~BaseNode() {}

            virtual std::string get_type() = 0;

            virtual ComponentGroupIds get_group_ids() = 0;

            virtual void init(EntityManager* em, EntityID entity_id) = 0;

    };

}
