#pragma once

#include <SFML/Window.hpp>

#include "../system.hpp"

namespace rh {

    enum struct MovementIntent {
        None,
        MoveForward,
        MoveBackward,
        Jump
    };

    class MovementSystem : public System {

        public:
            using System::System;

            void process(sf::RenderWindow *window);

    };

}
