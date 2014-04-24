#pragma once

#include "../component.hpp"
#include <SFML/Graphics.hpp>

namespace rh {
    namespace components {
        struct Position : public rh::Component<Position> {

            Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

            float x, y;

            // TODO: What about things that have a position but are not drawn?
            // New component Transformable?
            sf::Transformable *transformable;

        };
    }
}
