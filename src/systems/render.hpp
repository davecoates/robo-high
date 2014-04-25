#pragma once

#include "../system.hpp"

namespace rh {

    class RenderSystem : public System {

        public:
            void process(sf::RenderWindow *window);
    };

}
