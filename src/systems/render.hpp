#pragma once

#include "../system.hpp"

namespace rh {

    class RenderSystem : public System {

        public:
            using System::System;
            void process(sf::RenderWindow *window, const EntityVector&);
    };

}
