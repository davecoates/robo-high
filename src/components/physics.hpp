#pragma once

#include "../component.hpp"

namespace RHComponents {
    struct Physics : public RH::Component<Physics> {

        Physics(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

        float x, y;

    };
}
