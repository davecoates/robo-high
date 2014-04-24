#pragma once

#include "../component.hpp"
#include <SFML/Graphics.hpp>

namespace rh {
    namespace components {
        struct Transformable : public rh::Component<Transformable> {

            Transformable(sf::Transformable *transformable = nullptr) : transformable(transformable) {}

            sf::Transformable *transformable;
        };
    }
}
