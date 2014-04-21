#pragma once

#include "../component.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace RHComponents {

    struct Renderable : public RH::Component<Renderable> {
    
        Renderable(sf::Drawable *drawable = nullptr) : drawable(drawable) {}

        sf::Drawable *drawable;

    };
}
