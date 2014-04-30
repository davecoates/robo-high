#pragma once

#include <SFML/Window.hpp>

#include "../system.hpp"

#include "../nodes/movementnode.hpp"

namespace rh {

    enum struct MovementIntent {
        None,
        MoveForward,
        MoveBackward,
        Jump
    };

    class MovementSystem : public System {

        std::set<MovementNode*> nodes_;

        public:
            using System::System;

            void process(sf::RenderWindow *window);


            void add_node(BaseNode *node) {
                auto n = dynamic_cast<MovementNode*>(node);
                if (n) {
                    nodes_.insert(n);
                }
            }


    };

}
