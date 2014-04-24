#pragma once

#include "../component.hpp"
#include <SFML/Graphics.hpp>

namespace rh {
    namespace components {

        struct Renderable : public rh::Component<Renderable> {

            Renderable(sf::Drawable *drawable = nullptr) : drawable(drawable) {}

            sf::Drawable *drawable;

        };
    }
}
