#pragma once

#include <Box2d/Box2D.h>
#include <set>

#include "../component.hpp"

namespace rh {
    namespace components {
        // This is basically just a tag for now
        struct ContactSensor : public rh::Component<ContactSensor> {

            std::set<b2Fixture*> fixtures_in_contact;

        };
    }
}
