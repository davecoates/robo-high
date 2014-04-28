#pragma once

#include "../component.hpp"

namespace rh {
    namespace components {
        struct Movement : public rh::Component<Movement> {

            Movement(float h_speed = 5.0f, float v_speed = 5.0f) 
                : horizontal_speed(h_speed), vertical_speed(v_speed) {}

            float horizontal_speed;
            float vertical_speed;

        };
    }
}
