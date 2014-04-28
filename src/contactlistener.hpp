#pragma once

#include <Box2d/Box2D.h>
#include <set>
#include <iostream>

#include "entity.hpp"
#include "components/contactsensor.hpp"


//revised implementation of contact listener
namespace rh {
    class ContactListener : public b2ContactListener
    {
        rh::EntityManager* em_;

        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);


        public:
            ContactListener(rh::EntityManager* em) : em_(em) {}
    };
}
