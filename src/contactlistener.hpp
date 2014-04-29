#pragma once

#include <Box2d/Box2D.h>
#include <set>
#include <iostream>

#include "entity.hpp"
#include "components/contactsensor.hpp"
#include "physicsnode.hpp"

namespace rh {

    typedef std::map<EntityID, PhysicsNode*> PhysicsNodes;

    class ContactListener : public b2ContactListener
    {
        PhysicsNodes &physics_nodes_;

        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);


        public:
            ContactListener(PhysicsNodes &nodes) : physics_nodes_(nodes) {}
    };
}
