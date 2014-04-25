#pragma once

#include <SFML/Graphics.hpp>
#include "component.hpp"

namespace rh {

    class System {

        public:
            virtual void process(sf::RenderWindow *window) = 0;

            virtual void init_component(const unsigned int&, BaseComponent*) {}
    };

}
