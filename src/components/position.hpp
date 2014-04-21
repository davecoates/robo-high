#pragma once

#include "../component.hpp"

namespace RHComponents {
    struct Position : public RH::Component<Position> {

        Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

        float x, y;

    };
}
