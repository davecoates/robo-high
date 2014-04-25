#pragma once

#include <Box2d/Box2D.h>
#include <vector>

#include "../component.hpp"

namespace rh {
    namespace components {
        // This is basically just a tag for now
        struct Physics : public rh::Component<Physics> {

            Physics(b2BodyDef body_def, b2FixtureDef fixture) : body_def(body_def) {
                fixtures.push_back(fixture);
            }

            Physics(b2BodyDef body_def, std::initializer_list<b2FixtureDef> f) : body_def(body_def) {
                fixtures.insert(fixtures.end(), f.begin(), f.end());
            }

            b2BodyDef body_def;
            std::vector<b2FixtureDef> fixtures;

            // We only store this as Box2d body uses a pointer to refer to user
            // data
            unsigned int entity_id;
            
        };
    }
}
